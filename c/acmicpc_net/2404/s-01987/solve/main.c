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
    int r;
    int c;

    char line[20][21];
};
struct context_t context;

int dfs(struct context_t * ctx, int r, int c, int count, int mask)
{
    int max_count = count;
    int result;
    if (r > 0 && (mask & (1 << (ctx->line[r - 1][c] - 'A'))) == 0) {
        result = dfs(ctx, r - 1, c, count + 1, mask | (1 << (ctx->line[r - 1][c] - 'A')));
        if (max_count < result) {
            max_count = result;
        }
    }
    if (c > 0 && (mask & (1 << (ctx->line[r][c - 1] - 'A'))) == 0) {
        result = dfs(ctx, r, c - 1, count + 1, mask | (1 << (ctx->line[r][c - 1] - 'A')));
        if (max_count < result) {
            max_count = result;
        }
    }
    if (r < ctx->r - 1 && (mask & (1 << (ctx->line[r + 1][c] - 'A'))) == 0) {
        result = dfs(ctx, r + 1, c, count + 1, mask | (1 << (ctx->line[r + 1][c] - 'A')));
        if (max_count < result) {
            max_count = result;
        }
    }
    if (c < ctx->c - 1 && (mask & (1 << (ctx->line[r][c + 1] - 'A'))) == 0) {
        result = dfs(ctx, r, c + 1, count + 1, mask | (1 << (ctx->line[r][c + 1] - 'A')));
        if (max_count < result) {
            max_count = result;
        }
    }
    return max_count;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    result = dfs(ctx, 0, 0, 1, (1 << (ctx->line[0][0] - 'A')));

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->r);
    scanf("%d", &ctx->c);

    for (int r = 0; r < ctx->r; r++) {
        scanf("%s", ctx->line[r]);
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
