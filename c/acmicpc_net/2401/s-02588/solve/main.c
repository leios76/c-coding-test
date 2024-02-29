#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int a;
    int b;
};
struct context_t context;

int solve(struct context_t * ctx)
{
    printf("%d\n", (ctx->b % 10) * ctx->a);
    printf("%d\n", ((ctx->b / 10) % 10) * ctx->a);
    printf("%d\n", ((ctx->b / 100) % 10) * ctx->a);
    printf("%d\n", ctx->b * ctx->a);
    return 0;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d %d", &ctx->a, &ctx->b);
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
