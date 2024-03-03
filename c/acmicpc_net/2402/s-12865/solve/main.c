#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
    int k;
    int weights[100];
    int value[100];
    int dp[102][100000];
};
struct context_t context;

int get_dp(struct context_t * ctx, int index, int weight)
{
    int v;
    if (index >= ctx->n || weight == 0) {
        return 0;
    }

    if (ctx->dp[index][weight] == -1) {
        v = 0;
        if (weight >= ctx->weights[index]) {
            v = ctx->value[index] + get_dp(ctx, index + 1, weight - ctx->weights[index]);
            if (ctx->dp[index][weight] < v) {
                ctx->dp[index][weight] = v;
            }
        }
        v = get_dp(ctx, index + 1, weight);
        if (ctx->dp[index][weight] < v) {
            ctx->dp[index][weight] = v;
        }
    }

    return ctx->dp[index][weight];
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = get_dp(ctx, 0, ctx->k);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dp, -1, sizeof(ctx->dp));
    scanf("%d %d", &ctx->n, &ctx->k);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d %d", &ctx->weights[n], &ctx->value[n]);
    }
}

int main(int argc, char ** argv)
{
    int t = 1;

    //scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
