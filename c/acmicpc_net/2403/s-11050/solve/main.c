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
    int k;
    int dp[11];
};
struct context_t context;

int get_factorial(struct context_t * ctx, int n)
{
    if (n == 0 || n == 1) {
        return 1;
    }
    if (ctx->dp[n] != -1) {
        return ctx->dp[n];
    }
    ctx->dp[n] = n * get_factorial(ctx, n - 1);
    return ctx->dp[n];
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = get_factorial(ctx, ctx->n) / ( get_factorial(ctx, ctx->n - ctx->k) * get_factorial(ctx, ctx->k));
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->k);
    memset(ctx->dp, -1, sizeof(ctx->dp));
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
