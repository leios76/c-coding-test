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
    int n[3];
    int count[10];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 1;
    for (int n = 0; n < 3; n++) {
        result = result * ctx->n[n];
    }

    do {
        ctx->count[result % 10]++;
        result = result / 10;
    } while (result > 0);

    for (int i = 0; i < 10; i++) {
        printf("%d\n", ctx->count[i]);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    for (int n = 0; n < 3; n++) {
        scanf("%d", &ctx->n[n]);
    }
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
