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
    int t[5001];
    int dp[5001][10][10][10];
    int table[0x100];
};
struct context_t context;

void init_table(struct context_t * ctx)
{
    for (int a = 0; a < 10; a++) {
        for (int b = 0; b < 10; b++) {
            if (abs(a - b) > 10 - abs(a - b)) {
                ctx->table[a * 16 + b] = 10 - abs(a - b);
            } else {
                ctx->table[a * 16 + b] = abs(a - b);
            }
        }
    }
}

int r(struct context_t * ctx, int i, int x, int y, int z, int depth)
{
    int t;
    if (ctx->n == i) {
        return 0;
    }
    if (ctx->dp[i][x][y][z] == -1) {
        ctx->dp[i][x][y][z] = 1e9;
        t = r(ctx, i + 1, ctx->t[i + 1], y, z, depth + 1) + ctx->table[(x << 4) | ctx->t[i + 1]];
        if (ctx->dp[i][x][y][z] > t) {
            ctx->dp[i][x][y][z] = t;
        }
        t = r(ctx, i + 1, x, ctx->t[i + 1], z, depth + 1) + ctx->table[(y << 4) | ctx->t[i + 1]];
        if (ctx->dp[i][x][y][z] > t) {
            ctx->dp[i][x][y][z] = t;
        }
        t = r(ctx, i + 1, x, y, ctx->t[i + 1], depth + 1) + ctx->table[(z << 4) | ctx->t[i + 1]];
        if (ctx->dp[i][x][y][z] > t) {
            ctx->dp[i][x][y][z] = t;
        }
    }
    return ctx->dp[i][x][y][z];
}

int solve(struct context_t * ctx)
{
    return r(ctx, 0, 0, 0, 0, 0);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->n);
    for (int i = 1; i <= ctx->n; i++) {
        scanf("%d", &ctx->t[i]);
    }
    memset(ctx->dp, -1, sizeof(ctx->dp));
    init_table(ctx);
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
