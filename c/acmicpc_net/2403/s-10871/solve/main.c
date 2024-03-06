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
    int x;
    int a[10000];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    for (int n = 0; n < ctx->n; n++) {
        if (ctx->a[n] < ctx->x) {
            printf("%d ", ctx->a[n]);
        }
    }
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->x);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->a[n]);
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
