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
    uint8_t map[128][128];
};
struct context_t context;

int get_bit_count(struct context_t * ctx, int x, int y, int size, int color)
{
    int count = 0;
    for (int h = 0; h < size; h++) {
        for (int w = 0; w < size; w++) {
            int dx = x + w;
            int dy = y + h;

            if (ctx->map[dy][dx] == color) {
                count++;
            }
        }
    }
    return count;
}

int get_count(struct context_t * ctx, int x, int y, int size, int color)
{
    int count = 0;
    int bit_count;
    int half_size = size / 2;

    bit_count = get_bit_count(ctx, x, y, size, color);
    if (bit_count == size * size) {
        count = 1;
    } else if (size > 1) {
        count += get_count(ctx, x, y, half_size, color);
        count += get_count(ctx, x + half_size, y, half_size, color);
        count += get_count(ctx, x, y + half_size, half_size, color);
        count += get_count(ctx, x + half_size, y + half_size, half_size, color);
    }
    return count;
}

void solve(struct context_t * ctx)
{
    printf("%d\n", get_count(ctx, 0, 0, ctx->n, 0));
    printf("%d\n", get_count(ctx, 0, 0, ctx->n, 1));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int ny = 0; ny < ctx->n; ny++) {
        for (int nx = 0; nx < ctx->n; nx++) {
            scanf("%d", &ctx->map[ny][nx]);
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
