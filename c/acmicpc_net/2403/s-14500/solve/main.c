#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

#define S 0xFFFF

struct block_t {
    int width;
    int height;
    int shape[16];
};

struct block_t blocks[] = {
    // 0
    {4, 1, {S, S, S, S,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},
    {1, 4, {S, 0, 0, 0,
            S, 0, 0, 0,
            S, 0, 0, 0,
            S, 0, 0, 0, }},

    // 2
    {2, 2, {S, S, 0, 0,
            S, S, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},

    // 3
    {2, 3, {S, 0, 0, 0,
            S, 0, 0, 0,
            S, S, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {0, 0, S, 0,
            S, S, S, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},
    {2, 3, {S, S, 0, 0,
            0, S, 0, 0,
            0, S, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {S, S, S, 0,
            S, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},

    // 7
    {2, 3, {0, S, 0, 0,
            0, S, 0, 0,
            S, S, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {S, 0, 0, 0,
            S, S, S, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},
    {2, 3, {S, S, 0, 0,
            S, 0, 0, 0,
            S, 0, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {S, S, S, 0,
            0, 0, S, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},

    // 11
    {2, 3, {S, 0, 0, 0,
            S, S, 0, 0,
            0, S, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {0, S, S, 0,
            S, S, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},
    {2, 3, {0, S, 0, 0,
            S, S, 0, 0,
            S, 0, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {S, S, 0, 0,
            0, S, S, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},

    // 15
    {3, 2, {S, S, S, 0,
            0, S, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},
    {2, 3, {S, 0, 0, 0,
            S, S, 0, 0,
            S, 0, 0, 0,
            0, 0, 0, 0, }},
    {3, 2, {0, S, 0, 0,
            S, S, S, 0,
            0, 0, 0, 0,
            0, 0, 0, 0, }},
    {2, 3, {0, S, 0, 0,
            S, S, 0, 0,
            0, S, 0, 0,
            0, 0, 0, 0, }},
};

struct context_t {
    int n;
    int m;
    int value[500][500];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int block_count = sizeof(blocks) / sizeof(struct block_t);
    int sum;
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            for (int b = 0; b < block_count; b++) {
                if (m + blocks[b].width <= ctx->m && n + blocks[b].height <= ctx->n) {
                    sum = 0;
                    //debug("start %d,%d %d block\n", n, m, b);
                    for (int j = 0; j < 4; j++) {
                        for (int i = 0; i < 4; i++) {
                            //debug("%2d+", (blocks[b].shape[j * 4 + i] & ctx->value[n + j][m + i]));
                            sum += (blocks[b].shape[j * 4 + i] & ctx->value[n + j][m + i]);
                        }
                    }
                    //debug("=%d\n", sum);
                    if (sum > result) {
                        //debug("%d,%d %d block = %d\n", n, m, b, sum);
                        result = sum;
                    }
                } else {
                    //debug("skip %d,%d %d block (%dx%d)\n", n, m, b, blocks[b].width, blocks[b].height);
                }
            }
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            scanf("%d", &ctx->value[n][m]);
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
