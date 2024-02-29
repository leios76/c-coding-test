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
    char str1[1001];
    char str2[1001];

    int str1_length;
    int str2_length;

    int dp[1001][1001];
};
struct context_t context;

int debug_count = 0;

int get_dp(struct context_t * ctx, int index1, int index2)
{
    if (ctx->dp[index1][index2] > -1) {
        return ctx->dp[index1][index2];
    }
    if (index1 == 0 || index2 == 0) {
        return 0;
    }
    int d = 0;
    if (ctx->str1[index1 - 1] == ctx->str2[index2 - 1]) {
        ctx->dp[index1][index2] = 1 + get_dp(ctx, index1 - 1, index2 - 1);
    } else {
        d = get_dp(ctx, index1 - 1, index2);
        if (ctx->dp[index1][index2] < d) {
            ctx->dp[index1][index2] = d;
        }
        d = get_dp(ctx, index1, index2 - 1);
        if (ctx->dp[index1][index2] < d) {
            ctx->dp[index1][index2] = d;
        }
    }

    return ctx->dp[index1][index2];
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = get_dp(ctx, ctx->str1_length, ctx->str2_length);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%s", ctx->str1);
    scanf("%s", ctx->str2);

    ctx->str1_length = strlen(ctx->str1);
    ctx->str2_length = strlen(ctx->str2);
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
