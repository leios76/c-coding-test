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
    int v[2][100001];
    int dp[3][100001];
};
struct context_t context;

int max(int a, int b, int c)
{
    if (a >= b && a >= c) {
        return a;
    }
    if (b >= a && b >= c) {
        return b;
    }
    if (c >= a && c >= b) {
        return c;
    }
}
void solve(struct context_t * ctx)
{
    int result = 0;

    ctx->dp[0][1] = ctx->v[0][1];
    ctx->dp[1][1] = ctx->v[1][1];
    ctx->dp[2][1] = 0;

    for (int n = 2; n <= ctx->n; n++) {
        ctx->dp[0][n] = ctx->v[0][n] + max(ctx->dp[1][n - 1], ctx->dp[2][n - 1], 0);
        ctx->dp[1][n] = ctx->v[1][n] + max(ctx->dp[0][n - 1], ctx->dp[2][n - 1], 0);
        ctx->dp[2][n] = max(ctx->dp[0][n - 1], ctx->dp[1][n - 1], ctx->dp[2][n - 1]);
    }

    printf("%d\n", max(ctx->dp[0][ctx->n], ctx->dp[1][ctx->n], ctx->dp[2][ctx->n]));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int i = 0; i < 2; i++) {
        for (int n = 1; n <= ctx->n; n++) {
            scanf("%d", &ctx->v[i][n]);
        }
    }
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
