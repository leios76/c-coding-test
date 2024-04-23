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
    int a;
    int b;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    printf("%d + %d = %d\n", ctx->a, ctx->b, ctx->a + ctx->b);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->a);
    scanf("%d", &ctx->b);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        printf("Case #%d: ", i + 1);
        init_data(&context);
        solve(&context);
    }
    return 0;
}
