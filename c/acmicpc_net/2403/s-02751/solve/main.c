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
    int numbers[1000001];
    uint32_t bitmap2[2001023 / 1024];
    uint32_t bitmap1[2001023 / 32];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    for (int n = 0; n < 2001023; n++) {
        if (ctx->bitmap2[n / 1024] == 0) {
            n += 1023;
        } else if (ctx->bitmap1[n / 32] == 0) {
            n += 31;
        } else {
            if (ctx->bitmap1[n / 32] & (1 << (n % 32))) {
                printf("%d\n", n - 1000000);
            }
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->numbers[n]);
        int v = (ctx->numbers[n] + 1000000);
        ctx->bitmap2[v / 1024] |= (1 << ((v / 32)%32));
        ctx->bitmap1[v / 32] |= (1 << (v%32));
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
