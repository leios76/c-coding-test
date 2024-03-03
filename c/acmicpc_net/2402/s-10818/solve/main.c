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
    int min;
    int max;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    printf("%d %d\n", ctx->min, ctx->max);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);

    int value;
    ctx->min = 1000001;
    ctx->max = -1000001;

    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &value);

        if (ctx->min > value) {
            ctx->min = value;
        }
        if (ctx->max < value) {
            ctx->max = value;
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
