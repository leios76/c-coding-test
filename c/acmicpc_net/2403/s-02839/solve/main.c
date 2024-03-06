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
    int dp[5011];
};
struct context_t context;

int get(struct context_t * ctx, int remain)
{
    if (remain < 0) {
        return -1;
    } else if (remain == 0) {
        return 0;
    }

    if (ctx->dp[remain] != -1) {
        debug("dp get %d => %d\n", remain, ctx->dp[remain]);
        return ctx->dp[remain];
    }

    int min_count = 0x7FFFFFF;
    int count;

    debug("calc %d\n", remain);
    count = 1 + get(ctx, remain - 3);
    if (count > 0 && count < min_count) {
        min_count = count;
        ctx->dp[remain] = count;
        debug("dp set %d => %d\n", remain, ctx->dp[remain]);
    }
    count = 1 + get(ctx, remain - 5);
    if (count > 0 && count < min_count) {
        min_count = count;
        ctx->dp[remain] = count;
        debug("dp set %d => %d\n", remain, ctx->dp[remain]);
    }

    debug("get %d => %d\n", remain, ctx->dp[remain]);
    return ctx->dp[remain];
}

void solve(struct context_t * ctx)
{
    int result = 0;

    result = get(ctx, ctx->n);

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    memset(ctx->dp, -1, sizeof(ctx->dp));
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
