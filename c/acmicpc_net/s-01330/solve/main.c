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
    if (ctx->n > ctx->m) {
        printf(">\n");
    } else if (ctx->n < ctx->m) {
        printf("<\n");
    } else if (ctx->n == ctx->m) {
        printf("==\n");
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d %d", &ctx->n, &ctx->m);
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
