#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
    int dp[1001];
};
struct context_t context;

int get_dp(struct context_t * ctx, int pos)
{
    int count = 0;

    if (ctx->dp[pos] != -1) {
        return ctx->dp[pos];
    }
    if (pos == ctx->n) {
        return 1;
    }
    if (pos > ctx->n) {
        return 0;
    }
    if (pos + 1 <= ctx->n) {
        count += get_dp(ctx, pos + 1);
    }
    if (pos + 2 <= ctx->n) {
        count += get_dp(ctx, pos + 2);
    }
    if (pos + 2 <= ctx->n) {
        count += get_dp(ctx, pos + 2);
    }
    ctx->dp[pos] = count % 10007;
    return ctx->dp[pos];
}

void solve(struct context_t * ctx)
{
    printf("%d\n", get_dp(ctx, 0));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dp, -1, sizeof(ctx->dp));
    scanf("%d", &ctx->n);
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
