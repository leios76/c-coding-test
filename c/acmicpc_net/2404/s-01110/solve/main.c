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
    int v[3];
    int cycle;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    ctx->v[0] = ctx->n % 10;
    ctx->v[2] = ctx->n / 10;

    while (1) {
        ctx->cycle++;
        ctx->v[ctx->cycle % 3] = (ctx->v[(ctx->cycle + 2) % 3] + ctx->v[(ctx->cycle + 1) % 3]) % 10;
        debug("[%d] %d %d %d => %d\n", ctx->cycle, ctx->v[0], ctx->v[1], ctx->v[2], ctx->v[ctx->cycle % 3] + ctx->v[(ctx->cycle + 2) % 3] * 10);
        if (ctx->v[ctx->cycle % 3] + ctx->v[(ctx->cycle + 2) % 3] * 10 == ctx->n) {
            break;
        }
    }

    printf("%d\n", ctx->cycle);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
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
