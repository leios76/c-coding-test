#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int x;
    int y;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    int distance = ctx->y - ctx->x;
    int max = (sqrt(1.0f + 4.0f * (double)distance) - 1.0f) / 2.0f;
    int remain = distance - (max * (max + 1));

    debug("distance %d, max %d, remain %d\n", distance, max, remain);
    result = max * 2;
    while (remain > 0) {
        remain -= (max + 1);
        result++;
    }

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d %d", &ctx->x, &ctx->y);
}

int main(int argc, char ** argv)
{
    int t;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }

    return 0;
}
