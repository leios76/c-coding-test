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
    int dp[201][201];
};
struct context_t context;

int get_dp(struct context_t * ctx, int prev3, int prev2, int prev1, int sum, int depth)
{
    int count = 0;
    if (depth > ctx->k) {
        return 0;
    }
    if (sum == ctx->n) {
        for (int d = 0; d < depth; d++) {
            debug(">");
        }
        debug(" get dp %d + %d + %d = %d, %d\n", prev3, prev2, prev1, sum, depth);
        for (int d = 0; d < depth; d++) {
            debug(">");
        }
        debug("  count++\n");
        return 1;
    }
    if (sum > ctx->n) {
        return 0;
    }
    if (ctx->dp[depth][sum] != -1) {
        return ctx->dp[depth][sum];
    }
    for (int n = 0; n <= ctx->n; n++) {
        count += get_dp(ctx, prev2, prev1, n, sum + n, depth + 1);
        count = count % 1000000000;
    }
    ctx->dp[depth][sum] = count;
    return ctx->dp[depth][sum];
}

void solve(struct context_t * ctx)
{
    int result = 0;

    printf("%d\n", get_dp(ctx, 0, 0, 0, 0, 0));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dp, -1, sizeof(ctx->dp));
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
