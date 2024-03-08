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
    int k;
    int n;
    int map[15][15];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n = 1; n <= ctx->n; n++) {
        ctx->map[0][n] = n;
    }
    for (int k = 1; k <= ctx->k; k++) {
        for (int n = 1; n <= ctx->n; n++) {
            for (int s = 1; s <= n; s++) {
                ctx->map[k][n] += ctx->map[k - 1][s];
            }
        }
    }

    printf("%d\n", ctx->map[ctx->k][ctx->n]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->k);
    scanf("%d", &ctx->n);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
