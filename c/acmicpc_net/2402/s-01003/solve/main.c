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
    int t;
    int n[1000];
    int dp_f[42];
    int dp_1[42];
    int dp_0[42];
};
struct context_t context;

int fibonacci(struct context_t * ctx, int n)
{
    if (ctx->dp_f[n] != 0) {
        return ctx->dp_f[n];
    }
    if (n == 0) {
        ctx->dp_f[n] = 0;
        ctx->dp_0[n] = 1;
        ctx->dp_1[n] = 0;
        return 0;
    } else if (n == 1) {
        ctx->dp_f[n] = 1;
        ctx->dp_0[n] = 0;
        ctx->dp_1[n] = 1;
        return 1;
    } else {
        ctx->dp_f[n] = fibonacci(ctx, n - 1) + fibonacci(ctx, n - 2);
        ctx->dp_0[n] = ((n - 1 > -1) ? ctx->dp_0[n - 1]:0) + ((n - 2 > -1) ? ctx->dp_0[n - 2] : 0);
        ctx->dp_1[n] = ((n - 1 > -1) ? ctx->dp_1[n - 1]:0) + ((n - 2 > -1) ? ctx->dp_1[n - 2] : 0);
        return ctx->dp_f[n];
    }
}

void solve(struct context_t * ctx)
{
    for (int t = 0; t < ctx->t; t++) {
        memset(ctx->dp_f, 0, sizeof(ctx->dp_f));
        memset(ctx->dp_0, 0, sizeof(ctx->dp_0));
        memset(ctx->dp_1, 0, sizeof(ctx->dp_1));

        fibonacci(ctx, ctx->n[t]);

        printf("%d %d\n", ctx->dp_0[ctx->n[t]], ctx->dp_1[ctx->n[t]]);
    }
    return 0;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->t);
    for (int i = 0; i < ctx->t; i++) {
        scanf("%d", &ctx->n[i]);
    }
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
