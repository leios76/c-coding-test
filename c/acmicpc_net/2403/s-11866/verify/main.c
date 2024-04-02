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
    int k;
    int ni[1001];
    int oi[1001];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int count = ctx->n;
    int index = 0;
    int ni = 0;
    int oi = 0;
    for (int n = 0; n < ctx->n; n++) {
        ctx->ni[n] = n + 1;
    }

    while (count > 0) {
        if ((++index % ctx->k) == 0) {
            ctx->oi[oi++] = ctx->ni[ni];
            ctx->ni[ni] = -1;
            count--;
        }
        if (count == 0) {
            break;
        }
        do {
            ni = (ni + 1) % ctx->n;
        } while (ctx->ni[ni] == -1);
    }
    printf("<");
    for (int n = 0; n < ctx->n; n++) {
        if (n == oi - 1) {
            printf("%d", ctx->oi[n]);
        } else {
            printf("%d, ", ctx->oi[n]);
        }
    }
    printf(">\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->k);
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
