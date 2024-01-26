#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
};
struct context_t context;

int get(int depth, int n)
{
    if (depth == 0) {
        return 1;
    }
    switch (n) {
        case 0:
            return get(depth - 1, 0) + get(depth - 1, 1) + get(depth - 1, 2) + get(depth - 1, 4) + get(depth - 1, 5);
        case 1:
            return get(depth - 1, 0) + get(depth - 1, 2) + get(depth - 1, 4);
        case 2:
            return get(depth - 1, 0) + get(depth - 1, 1) + get(depth - 1, 4) + get(depth - 1, 5);
        case 4:
            return get(depth - 1, 0) + get(depth - 1, 1) + get(depth - 1, 2);
        case 5:
            return get(depth - 1, 0) + get(depth - 1, 2);
    }
}

int solve(struct context_t * ctx)
{
    return get(ctx->n, 0);
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
