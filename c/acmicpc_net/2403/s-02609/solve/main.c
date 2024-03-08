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
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int large_number;
    int n;
    if (ctx->n > ctx->m) {
        large_number = ctx->n;
    } else {
        large_number = ctx->m;
    }

    for (n = large_number; n > 0; n--) {
        if ((ctx->n % n) == 0 && (ctx->m % n) == 0) {
            printf("%d\n", n);
            break;
        }
    }
    printf("%d\n", ctx->n * ctx->m / n);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);
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
