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
    int x;
    int y;
};
struct context_t context;

int get_number(int m, int n, int x, int y, int max)
{
    int i = 0;
    while (1) {
        debug("%d\n", (x + i*m));
        if ((x + i*m) % n == y % n) {
            return (x + i*m);
        }
        i++;
        if ((x + i*m) > max) {
            break;
        }
    }
    return -1;
}

void solve(struct context_t * ctx)
{
    int last = get_number(ctx->m, ctx->n, ctx->m, ctx->n, ctx->m * ctx->n);
    debug("last %d\n", last);
    printf("%d\n", get_number(ctx->m, ctx->n, ctx->x, ctx->y, last));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->m);
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->x);
    scanf("%d", &ctx->y);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
