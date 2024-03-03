#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    char name[64];
};
struct context_t context;

int solve(struct context_t * ctx)
{
    printf("%s??!\n", ctx->name);
    return 0;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%s", ctx->name);
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
