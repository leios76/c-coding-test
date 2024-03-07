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
    int n;
};
struct context_t context;

int get(int n)
{
    int r = n;
    while (n > 0) {
        r += (n % 10);
        n = n / 10;
    }
    return r;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n = 1; n < ctx->n; n++) {
        if (get(n) == ctx->n) {
            printf("%d\n", n);
            return;
        }
    }

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
}

int main(int argc, char ** argv)
{
    int t = 1;

    //scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
