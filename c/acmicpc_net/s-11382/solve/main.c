#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int64_t a;
    int64_t b;
    int64_t c;
};
struct context_t context;

int64_t solve(struct context_t * ctx)
{
    return ctx->a + ctx->b + ctx->c;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%ld %ld %ld", &ctx->a, &ctx->b, &ctx->c);
}

int main()
{
    init_data(&context);
    printf("%ld\n", solve(&context));

    return 0;
}
