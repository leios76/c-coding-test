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
    int t;
    int map_index;
    int upper_clear_r;
    int lower_clear_r;

    int map[2][50][50];
};
struct context_t context;

void spread(struct context_t * ctx)
{
    int next_map_index = (ctx->map_index + 1) % 2;
    memset(&ctx->map[next_map_index], 0, sizeof(ctx->map[next_map_index]));
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    for (int r = 0; r < ctx->r; r++) {
        for (int c = 0; c < ctx->c; c++) {
            int spread = ctx->map[ctx->map_index][r][c] / 5;
            int total = 0;
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < ctx->r && nc >= 0 && nc < ctx->c && ctx->map[ctx->map_index][nr][nc] != -1) {
                    if ((nr == ctx->upper_clear_r || nr == ctx->lower_clear_r) && nc == 0) {
                        continue;
                    }
                    ctx->map[next_map_index][nr][nc] += spread;
                    total += spread;
                }
            }
            ctx->map[next_map_index][r][c] += ctx->map[ctx->map_index][r][c] - total;
        }
    }
    ctx->map_index = next_map_index;
}

void clean(struct context_t * ctx)
{
    for (int r = ctx->upper_clear_r - 1; r > 0; r--) {
        ctx->map[ctx->map_index][r][0] = ctx->map[ctx->map_index][r - 1][0];
    }
    for (int c = 1; c < ctx->c; c++) {
        ctx->map[ctx->map_index][0][c - 1] = ctx->map[ctx->map_index][0][c];
    }
    for (int r = 1; r <= ctx->upper_clear_r; r++) {
        ctx->map[ctx->map_index][r - 1][ctx->c - 1] = ctx->map[ctx->map_index][r][ctx->c - 1];
    }
    for (int c = ctx->c - 1; c >= 2; c--) {
        ctx->map[ctx->map_index][ctx->upper_clear_r][c] = ctx->map[ctx->map_index][ctx->upper_clear_r][c - 1];
    }
    ctx->map[ctx->map_index][ctx->upper_clear_r][1] = 0;

    for (int r = ctx->lower_clear_r + 1; r < ctx->r - 1; r++) {
        ctx->map[ctx->map_index][r][0] = ctx->map[ctx->map_index][r + 1][0];
    }
    for (int c = 1; c < ctx->c; c++) {
        ctx->map[ctx->map_index][ctx->r - 1][c - 1] = ctx->map[ctx->map_index][ctx->r - 1][c];
    }
    for (int r = ctx->r - 1; r > ctx->lower_clear_r; r--) {
        ctx->map[ctx->map_index][r][ctx->c - 1] = ctx->map[ctx->map_index][r - 1][ctx->c - 1];
    }
    for (int c = ctx->c - 1; c >= 2; c--) {
        ctx->map[ctx->map_index][ctx->lower_clear_r][c] = ctx->map[ctx->map_index][ctx->lower_clear_r][c - 1];
    }
    ctx->map[ctx->map_index][ctx->lower_clear_r][1] = 0;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    for (int t = 0; t < ctx->t; t++) {
        spread(ctx);
        clean(ctx);
    }

    for (int r = 0; r < ctx->r; r++) {
        for (int c = 0; c < ctx->c; c++) {
            if (ctx->map[ctx->map_index][r][c] != -1) {
                result += ctx->map[ctx->map_index][r][c];
            }
        }
    }

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    ctx->upper_clear_r = -1;
    ctx->lower_clear_r = -1;

    scanf("%d", &ctx->r);
    scanf("%d", &ctx->c);
    scanf("%d", &ctx->t);
    for (int r = 0; r < ctx->r; r++) {
        for (int c = 0; c < ctx->c; c++) {
            scanf("%d", &ctx->map[0][r][c]);
            if (ctx->map[0][r][c] == -1) {
                if (ctx->upper_clear_r == -1) {
                    ctx->upper_clear_r = r;
                } else {
                    ctx->lower_clear_r = r;
                }
            }
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
