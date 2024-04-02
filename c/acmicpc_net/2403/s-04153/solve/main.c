#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

int running = 1;

struct context_t {
    int a;
    int b;
    int c;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    if (ctx->a == 0 && ctx->b == 0 && ctx->c == 0) {
        running = 0;
        return;
    }

    if (ctx->a >= ctx->b && ctx->a >= ctx->c) {
        if (ctx->a * ctx->a == ctx->b * ctx->b + ctx->c * ctx->c) {
            result = 1;
        }
    } else if (ctx->b >= ctx->a && ctx->b >= ctx->c) {
        if (ctx->b * ctx->b == ctx->a * ctx->a + ctx->c * ctx->c) {
            result = 1;
        }
    } else if (ctx->c >= ctx->a && ctx->c >= ctx->b) {
        if (ctx->c * ctx->c == ctx->a * ctx->a + ctx->b * ctx->b) {
            result = 1;
        }
    }

    printf("%s\n", result?"right":"wrong");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d%d", &ctx->a, &ctx->b, &ctx->c);
}

int main(int argc, char ** argv)
{
    int t = 1;

    //scanf("%d", &t);
    while (running) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
