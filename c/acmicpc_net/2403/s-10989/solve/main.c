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
    int a[10001];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int i = 0; i < 10001; i++) {
        for (int j = 0; j < ctx->a[i]; j++) {
            printf("%d\n", i);
        }
    }
}

void init_data(struct context_t * ctx)
{
    int v;
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &v);
        ctx->a[v]++;
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
