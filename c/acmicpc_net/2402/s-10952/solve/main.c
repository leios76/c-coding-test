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
    int a;
    int b;
};
struct context_t context;

void solve(struct context_t * ctx)
{
}

void init_data(struct context_t * ctx)
{
    while (1) {
        memset(ctx, 0, sizeof(struct context_t));
        scanf("%d %d", &ctx->a, &ctx->b);
        if (ctx->a == 0 && ctx->b == 0) {
            break;
        }
        printf("%d\n", ctx->a + ctx->b);
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
