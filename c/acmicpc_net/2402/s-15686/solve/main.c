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
    int map[50][50];
    int house[100];
    int shop[13];
    int house_count;
    int shop_count;
    int distance[100][13];
    uint8_t min_distance[100];
    int total_distance;
    uint32_t shop_mask;
};
struct context_t context;

void calc_distance(struct context_t * ctx)
{
    for (int h = 0; h < ctx->house_count; h++) {
        for (int s = 0; s < ctx->shop_count; s++) {
            ctx->distance[h][s] = abs( (ctx->house[h] >> 8) - (ctx->shop[s] >> 8) ) + abs( (ctx->house[h] & 0xFF) - (ctx->shop[s] & 0xFF) );
            debug("%d ", ctx->distance[h][s]);
        }
        debug("\n");
    }
}

void calc_min_distance(struct context_t * ctx, int shop_mask)
{
    memset(ctx->min_distance, 0xFF, sizeof(ctx->min_distance));

    for (int h = 0; h < ctx->house_count; h++) {
        for (int s = 0; s < ctx->shop_count; s++) {
            if (shop_mask & (1 << s)) {
                if (ctx->min_distance[h] > ctx->distance[h][s]) {
                    ctx->min_distance[h] = ctx->distance[h][s];
                }
            }
        }
        //debug("house %d(%d,%d) min distance = %d\n", h, ctx->house[h] >> 8, ctx->house[h] & 0xFF, ctx->min_distance[h]);
    }
}

int get_total_distance(struct context_t * ctx)
{
    int total = 0;
    for (int h = 0; h < ctx->house_count; h++) {
        total += ctx->min_distance[h];
    }
    return total;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    int count;


    int min_distance = 0x7FFFFFFF;
    int distance;
    int shop_mask = 0;

    calc_distance(ctx);

    while (1) {
        shop_mask++;
        if (shop_mask == (1 << ctx->shop_count)) {
            break;
        }
        count = 0;
        for (int s = 0; s < ctx->shop_count; s++) {
            if (shop_mask & (1 << s)) {
                count++;
            }
        }
        if (count <= ctx->m) {
            calc_min_distance(ctx, shop_mask);
            distance = get_total_distance(ctx);
            if (min_distance > distance) {
                ctx->shop_mask = shop_mask;
                min_distance = distance;
            }
        }
    }

    calc_min_distance(ctx, ctx->shop_mask);
    printf("%d\n", get_total_distance(ctx));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);
    for (int r = 0; r < ctx->n; r++) {
        for (int c = 0; c < ctx->n; c++) {
            scanf("%d", &ctx->map[r][c]);
            if (ctx->map[r][c] == 1) {
                ctx->house[ctx->house_count++] = (r << 8) | c;
            } else if (ctx->map[r][c] == 2) {
                ctx->shop[ctx->shop_count++] = (r << 8) | c;
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
