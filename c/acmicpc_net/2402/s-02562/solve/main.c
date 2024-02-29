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
    int n[9];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int index = 0;

    for (int i = 0; i < 9; i++) {
        if (result < ctx->n[i]) {
            result = ctx->n[i];
            index = i + 1;
        }
    }
    printf("%d\n", result);
    printf("%d\n", index);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    for (int i = 0; i < 9; i++) {
        scanf("%d", &ctx->n[i]);
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
