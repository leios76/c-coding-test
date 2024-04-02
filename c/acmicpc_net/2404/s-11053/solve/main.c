#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
    int v[1001];
    int dp[1001];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    for (int n1 = 0; n1 < ctx->n; n1++) {
        ctx->dp[n1] = 1;
        for (int n2 = n1 - 1; n2 >= 0; n2--) {
            if (ctx->v[n2] < ctx->v[n1]) {
                if (ctx->dp[n1] < ctx->dp[n2] + 1) {
                    ctx->dp[n1] = ctx->dp[n2] + 1;
                }
            }

        }
    }
    result = ctx->dp[0];
    for (int n = 1; n < ctx->n; n++) {
        if (result < ctx->dp[n]) {
            result = ctx->dp[n];
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->v[n]);
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
