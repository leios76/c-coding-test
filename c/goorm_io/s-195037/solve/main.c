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
    int w1;
    int h1;
    int w2;
    int h2;
    int count;
    int board1[30];
    int board2[30];
};
struct context_t context;



int solve(struct context_t * ctx)
{
    int max_count = 0;
    int max_w;
    int max_h;
    for (int h = 0; h < 20; h++) {
        for (int w = 0; w < 20; w++) {
            int c = 0;
            for (int l = 0; l < 10; l++) {
                // 3FF => 10bit
                int v = ((ctx->board1[20 + l - h] >> (20 - w)) & 0x3FF) & ((ctx->board2[10 + l] >> 10) & 0x3FF);
                for (int i = 0; i < 10; i++) {
                    if (v & (1 << i)) {
                        c++;
                    }
                }
                int b = (ctx->board1[20 + l - h] >> (20 - w)) & 0x3FF;
                debug("[%d] (0x%04X)", l, b);
                for (int j = 9; j >= 0; j--) {
                    if (b & (1 << j)) {
                        debug("O");
                    } else {
                        debug(".");
                    }
                }
                b = (ctx->board2[10 + l] >> 10) & 0x3FF;
                debug("  (0x%04X)", b);
                for (int j = 9; j >= 0; j--) {
                    if (b & (1 << j)) {
                        debug("O");
                    } else {
                        debug(".");
                    }
                }
                debug(" (%d)\n", c);
            }
            debug("h%d, w%d => %d\n", h, w, c);
            if (max_count < c) {
                max_count = c;
                max_w = w;
                max_h = h;
            }
        }
    }
    debug("h%d, w%d => %d\n", max_h, max_w, max_count);
    return ctx->count - max_count;
}

void init_data(struct context_t * ctx)
{
    char line[12];
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d %d", &ctx->h1, &ctx->w1);
    for (int h = 0; h < ctx->h1; h++) {
        scanf("%s", line);
        for (int w = 0; w < ctx->w1; w++) {
            if (line[w] == 'O') {
                ctx->board1[h + 10] |= (1 << (w + 10));
                ctx->count++;
            }
        }
    }

    scanf("%d %d", &ctx->h2, &ctx->w2);
    for (int h = 0; h < ctx->h2; h++) {
        scanf("%s", line);
        for (int w = 0; w < ctx->w2; w++) {
            if (line[w] == 'O') {
                ctx->board2[h + 10] |= (1 << (w + 10));
            }
        }
    }
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
