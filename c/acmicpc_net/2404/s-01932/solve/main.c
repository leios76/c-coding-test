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
    int v[500][500];
    int dp[500][500];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    ctx->dp[0][0] = ctx->v[0][0];
    for (int level = 1; level < ctx->n; level++) {
        for (int index = 0; index <= level; index++) {
            if (index == 0) {
                ctx->dp[level][index] = ctx->v[level][index] + ctx->dp[level - 1][index];
            } else if (index == level) {
                ctx->dp[level][index] = ctx->v[level][index] + ctx->dp[level - 1][index - 1];
            } else {
                if (ctx->dp[level - 1][index] < ctx->dp[level - 1][index - 1]) {
                    ctx->dp[level][index] = ctx->v[level][index] + ctx->dp[level - 1][index - 1];
                } else {
                    ctx->dp[level][index] = ctx->v[level][index] + ctx->dp[level - 1][index];
                }
            }
        }
    }
    for (int index = 0; index <= ctx->n; index++) {
        if (result < ctx->dp[ctx->n - 1][index]) {
            result = ctx->dp[ctx->n - 1][index];
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    int level = 0;
    int index;
    for (int n = 0; n < ctx->n; n++) {
        index = 0;
        for (int i = 0; i <= n; i++) {
            scanf("%d", &ctx->v[level][index++]);
        }
        level++;
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
