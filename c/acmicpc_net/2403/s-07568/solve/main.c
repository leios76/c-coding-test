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
    int w[50];
    int h[50];
};
struct context_t context;

int get_count(struct context_t * ctx, int i)
{
    int c = 0;
    for (int n = 0; n < ctx->n; n++) {
        if (ctx->w[i] < ctx->w[n] && ctx->h[i] < ctx->h[n]) {
            c++;
        }
    }
    return c;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n = 0; n < ctx->n; n++) {
        printf("%d ", get_count(ctx, n) + 1);
    }

    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d%d", &ctx->w[n], &ctx->h[n]);
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
