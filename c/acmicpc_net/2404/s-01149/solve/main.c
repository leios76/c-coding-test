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
    int price[1001][3];
    int dp[1001][3];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n = 1; n <= ctx->n; n++) {
        if (ctx->dp[n - 1][1] > ctx->dp[n - 1][2]) {
            ctx->dp[n][0] = ctx->price[n][0] + ctx->dp[n - 1][2];
        } else {
            ctx->dp[n][0] = ctx->price[n][0] + ctx->dp[n - 1][1];
        }

        if (ctx->dp[n - 1][0] > ctx->dp[n - 1][2]) {
            ctx->dp[n][1] = ctx->price[n][1] + ctx->dp[n - 1][2];
        } else {
            ctx->dp[n][1] = ctx->price[n][1] + ctx->dp[n - 1][0];
        }

        if (ctx->dp[n - 1][0] > ctx->dp[n - 1][1]) {
            ctx->dp[n][2] = ctx->price[n][2] + ctx->dp[n - 1][1];
        } else {
            ctx->dp[n][2] = ctx->price[n][2] + ctx->dp[n - 1][0];
        }
    }

    debug("%d %d %d\n", ctx->dp[ctx->n][0], ctx->dp[ctx->n][1], ctx->dp[ctx->n][2]);
    result = ctx->dp[ctx->n][0];
    if (result > ctx->dp[ctx->n][1]) {
        result = ctx->dp[ctx->n][1];
    }
    if (result > ctx->dp[ctx->n][2]) {
        result = ctx->dp[ctx->n][2];
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 1; n <= ctx->n; n++) {
        scanf("%d%d%d", &ctx->price[n][0], &ctx->price[n][1], &ctx->price[n][2]);
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
