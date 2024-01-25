#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
    int value[100001];
};
struct context_t context;

uint64_t min_value(uint64_t a, uint64_t b, uint64_t c)
{
    if (a <= b && a <= c) {
        return a;
    }
    if (b <= a && b <= c) {
        return b;
    }
    if (c <= a && c <= b) {
        return c;
    }
}

uint64_t solve(struct context_t * ctx)
{
    uint64_t sum[3];
    int index = -1;

    sum[0] = ctx->value[0];
    sum[1] = ctx->value[1];
    sum[2] = ctx->value[2];

    for (int i = 3; i < ctx->n; i++) {
        sum[i % 3] = min_value(sum[i % 3], sum[(i + 1) % 3], sum[(i + 2) % 3]) + (uint64_t)ctx->value[i];
    }

    return min_value(sum[0], sum[1], sum[2]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->n);

    for (int i = 0; i < ctx->n; i++) {
        scanf("%d", &ctx->value[i]);
    }
}

int main()
{
    init_data(&context);
    printf("%ld\n", solve(&context));

    return 0;
}
