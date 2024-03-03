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
    int t;
    int n[1000];
    int m[1000];
    int dp[31][31];
};
struct context_t context;

int get_r(struct context_t * ctx, int i, int depth, int start)
{
    if (ctx->dp[depth][start] != 0) {
        debug("  return dp %d\n", ctx->dp[depth][start]);
        return ctx->dp[depth][start];
    }
    if (depth == ctx->n[i]) {
        ctx->dp[depth][start] = 1;
        return ctx->dp[depth][start];
    }

    int sum = 0;
    for (int j = start + 1; j <= ctx->m[i] - ctx->n[i] + depth + 1; j++) {
        debug("[%d] get d%02d s%02d\n", i, depth + 1, j);
        sum += get_r(ctx, i, depth + 1, j);
    }
    ctx->dp[depth][start] = sum;
    return sum;
}

void solve(struct context_t * ctx)
{
    for (int i = 0; i < ctx->t; i++) {
        memset(ctx->dp, 0, sizeof(ctx->dp));
        printf("%d\n", get_r(ctx, i, 0, 0));
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->t);
    for (int i = 0; i < ctx->t; i++) {
        scanf("%d %d", &ctx->n[i], &ctx->m[i]);
    }
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
