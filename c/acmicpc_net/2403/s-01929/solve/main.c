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
    int m;
    int n;

    uint32_t bitmap2[2001023 / 1024];
    uint32_t bitmap1[2001023 / 32];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n = 2; n <= ctx->n; n++) {
        for (int i = n * 2; i <= ctx->n; i += n) {
            ctx->bitmap1[i / 32] &= ~(1 << (i % 32));
        }
    }

    for (int n = ctx->m; n <= ctx->n; n++) {
        if (ctx->bitmap1[n / 32] == 0) {
            n = (int)((n + 31) / 32) * 32;
        } else {
            if (ctx->bitmap1[n / 32] & (1 << (n % 32))) {
                printf("%d\n", n);
            }
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->m, &ctx->n);
    memset(ctx->bitmap1, 0xFF, sizeof(ctx->bitmap1));
    ctx->bitmap1[0] &= ~((1 << 0) | (1 << 1));
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
