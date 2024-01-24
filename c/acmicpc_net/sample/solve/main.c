#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
};
struct context_t context;

int solve(struct context_t * ctx)
{
    return 0;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->n);
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
