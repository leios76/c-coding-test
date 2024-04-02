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
    int v[301];
    int dp[301];
};
struct context_t context;

int get_dp(struct context_t * ctx, int pos)
{
    debug("get_dp %d\n", pos);
    if (pos < 0) {
        return -16711680;
    }
    if (ctx->dp[pos] != -1) {
        return ctx->dp[pos];
    }

    int score = 0;
    int max_score = ctx->v[pos];
    if (pos == 2) {
        debug("dp[%d] = %d + dp[%d - 1]\n", pos, ctx->v[pos], pos);
        score = ctx->v[pos] + get_dp(ctx, pos - 1);
        if (score > max_score) {
            max_score = score;
        }
    }

    if (pos >= 2) {
        debug("2step dp[%d] = %d + dp[%d - 2]\n", pos, ctx->v[pos], pos);
        score = ctx->v[pos] + get_dp(ctx, pos - 2);
        if (score > max_score) {
            max_score = score;
        }
    }

    if (pos >= 3) {
        debug("1step dp[%d] = %d + %d + dp[%d - 3]\n", pos, ctx->v[pos - 1], ctx->v[pos], pos);
        score = ctx->v[pos - 1] + ctx->v[pos] + get_dp(ctx, pos - 3);
        if (score > max_score) {
            max_score = score;
        }
    } else {

    }

    ctx->dp[pos] = max_score;
    debug("set_dp %d = %d\n", pos, max_score);
    return ctx->dp[pos];
}

void solve(struct context_t * ctx)
{
    int result = 0;
    ctx->dp[0] = 0;
    result = get_dp(ctx, ctx->n);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dp, -1, sizeof(ctx->dp));
    scanf("%d", &ctx->n);
    for (int n = 1; n <= ctx->n; n++) {
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
