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
    int v;
    int c;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int d = ctx->a - ctx->b;
    ctx->c = (int)((ctx->v - ctx->a)/d) * d;
    result += (int)((ctx->v - ctx->a)/d);
    while (ctx->c < ctx->v) {
        result++;
        ctx->c += ctx->a;
        if (ctx->c >= ctx->v) {
            break;
        }
        ctx->c -= ctx->b;
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d%d", &ctx->a, &ctx->b, &ctx->v);
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
