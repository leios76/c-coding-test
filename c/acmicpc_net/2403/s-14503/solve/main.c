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

    int r;
    int c;
    int d;

    int map[50][50];
};
struct context_t context;

int diff_r[4] = {-1, 0, 1, 0};
int diff_c[4] = {0, 1, 0, -1};

int move(struct context_t * ctx)
{
    int dr;
    int dc;
    int d;
    debug("scan %d,%d(%d)\n", ctx->r, ctx->c, ctx->d);
    for (d = 0; d < 4; d++) {
        dr = diff_r[(ctx->d + 8 - d - 1)%4];
        dc = diff_c[(ctx->d + 8 - d - 1)%4];

        if (ctx->r + dr < 0 || ctx->r + dr > ctx->n - 1 || ctx->c + dc < 0 || ctx->c + dc > ctx->m - 1) {
            debug("skip %d,%d(%d) -> %d,%d\n", ctx->r, ctx->c, (ctx->d + 8 - d - 1) % 4, ctx->r + dr, ctx->c + dc);
            continue;
        }

        if (ctx->map[ctx->r + dr][ctx->c + dc] == 0) {
            debug("move %d,%d(%d) -> %d,%d\n", ctx->r, ctx->c, (ctx->d + 8 - d - 1) % 4, ctx->r + dr, ctx->c + dc);
            ctx->r += dr;
            ctx->c += dc;
            ctx->d = (ctx->d + 8 - d - 1) % 4;
            return 1;
        }
    }

    dr = diff_r[(ctx->d + 4 - d)%4];
    dc = diff_c[(ctx->d + 4 - d)%4];

    if (ctx->r - dr < 0 || ctx->r - dr > ctx->n - 1 || ctx->c - dc < 0 || ctx->c - dc > ctx->m - 1 || ctx->map[ctx->r - dr][ctx->c - dc] == 1) {
        debug("stop %d,%d(%d) -> %d,%d\n", ctx->r, ctx->c, (ctx->d + 8 - d) % 4, ctx->r - dr, ctx->c - dc);
        return 0;
    }
    debug("move %d,%d(%d) -> %d,%d\n", ctx->r, ctx->c, (ctx->d + 8 - d) % 4, ctx->r - dr, ctx->c - dc);
    ctx->r -= dr;
    ctx->c -= dc;
    return 1;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    while (1) {
        if (ctx->map[ctx->r][ctx->c] == 0) {
            debug("clean %d,%d\n", ctx->r, ctx->c);
            ctx->map[ctx->r][ctx->c] = 2;
            result++;
        } else {
            if (move(ctx) == 0) {
                break;
            }
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);
    scanf("%d%d%d", &ctx->r, &ctx->c, &ctx->d);
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            scanf("%d", &ctx->map[n][m]);
        }
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
