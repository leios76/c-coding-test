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
    int start;
    int end;
    int bus_start[100000];
    int bus_end[100000];
    int bus_price[100000];
    uint32_t distance[100000];
    int visited[1000];
};
struct context_t context;

int get_min_village(struct context_t * ctx)
{
    int min_value = 0x7FFFFFFF;
    int min_index = -1;
    for (int n = 0; n < ctx->n; n++) {
        if (!ctx->visited[n]) {
            if (min_value > ctx->distance[n]) {
                min_index = n;
                min_value = ctx->distance[n];
            }
        }
    }
    return min_index;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    int n = ctx->start - 1;
    ctx->distance[n] = 0;

    do {
        debug("Checking village %d\n", n + 1);
        ctx->visited[n] = 1;
        for (int m = 0; m < ctx->m; m++) {
            debug("start %d, end %d, price %d\n", ctx->bus_start[m], ctx->bus_end[m], ctx->bus_price[m]);
            if (ctx->bus_start[m] - 1 == n && !ctx->visited[ctx->bus_end[m] - 1]) {
                uint32_t distance = ctx->distance[ctx->bus_start[m] - 1] + ctx->bus_price[m];
                if (ctx->distance[ctx->bus_end[m] - 1] > distance) {
                    debug("update village %d distance %d\n", ctx->bus_end[m], distance);
                    ctx->distance[ctx->bus_end[m] - 1] = distance;
                }
            }
        }
        n = get_min_village(ctx);
        debug(" next village: %d\n", n + 1);
    } while (n != -1);
    printf("%d\n", ctx->distance[ctx->end - 1]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d%d", &ctx->bus_start[m], &ctx->bus_end[m], &ctx->bus_price[m]);
    }
    scanf("%d%d", &ctx->start, &ctx->end);
    memset(ctx->distance, 0xFF, sizeof(ctx->distance));
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
