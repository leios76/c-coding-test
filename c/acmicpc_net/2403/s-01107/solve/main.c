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
    int m;
    int disabled_bits;
    int min_diff;
    int min_diff_channel;
};
struct context_t context;

void find_min_channel(struct context_t * ctx, int channel, int index, int rate)
{
    for (int b = 0; b < 10; b++) {
        if (ctx->disabled_bits & (1 << b)) {
            continue;
        }
        int ch;
        ch = channel + b * rate;
        int diff = abs(ctx->n - ch) + index + 1;
        if (ctx->min_diff > diff) {
            debug("ch %d - new min diff: %d + %d\n", ch, abs(ctx->n - ch), index);
            ctx->min_diff = diff;
            ctx->min_diff_channel = ch;
        }
        if (index < 5) {
            find_min_channel(ctx, channel + b * rate, index + 1, rate * 10);
        }
    }
}

void solve(struct context_t * ctx)
{
    int index = 0;
    ctx->min_diff = 0x7FFFFFF;
    find_min_channel(ctx, 0, 0, 1);

    if (ctx->min_diff < abs(ctx->n - 100)) {
        printf("%d\n", ctx->min_diff);
    } else {
        printf("%d\n", abs(ctx->n - 100));
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int m = 0; m < ctx->m; m++) {
        int d;
        scanf("%d", &d);
        ctx->disabled_bits |= (1 << d);
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
