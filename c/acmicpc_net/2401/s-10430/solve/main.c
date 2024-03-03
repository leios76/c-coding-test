#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int a;
    int b;
    int c;
};
struct context_t context;

int solve(struct context_t * ctx)
{
    printf("%d\n", (ctx->a + ctx->b) % ctx->c);
    printf("%d\n", ((ctx->a % ctx->c) + (ctx->b % ctx->c)) % ctx->c);
    printf("%d\n", (ctx->a * ctx->b) % ctx->c);
    printf("%d\n", ((ctx->a % ctx->c) * (ctx->b % ctx->c)) % ctx->c);
    return 0;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d %d %d", &ctx->a, &ctx->b, &ctx->c);
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
