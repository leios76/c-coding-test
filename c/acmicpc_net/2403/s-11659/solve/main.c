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
    int m;
    int v[100000];
    int s[100000];
    int e[100000];
    int dp[100000];
};
struct context_t context;

int get_dp(struct context_t * ctx, int n)
{
    if (n < 0) {
        return 0;
    }
    if (ctx->dp[n] != -1) {
        return ctx->dp[n];
    }
    ctx->dp[n] = ctx->v[n] + get_dp(ctx, n - 1);
    return ctx->dp[n];
}

void solve(struct context_t * ctx)
{
    int result = 0;
    ctx->dp[0] = ctx->v[0];
    for (int m = 0; m < ctx->m; m++) {
        printf("%d\n", get_dp(ctx, ctx->e[m] - 1) - get_dp(ctx, ctx->s[m] - 2));
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dp, -1, sizeof(ctx->dp));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->v[n]);
    }
    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d", &ctx->s[m], &ctx->e[m]);
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
