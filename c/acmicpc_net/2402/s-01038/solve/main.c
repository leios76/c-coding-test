#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

#define MAX_DIGITS  10

struct context_t {
    int n;
    int count;
    int digits[MAX_DIGITS];
};
struct context_t context;

void get_value(struct context_t * ctx, int depth)
{
    for (ctx->digits[depth] = 0; ctx->digits[depth] < 10; ctx->digits[depth]++) {
        for (int i = 0; i < depth; i++) {
            if (ctx->digits[i] != 0) {
                if (ctx->digits[depth] >= ctx->digits[depth - 1]) {
                    return;
                }
            }
        }
        if (depth + 1 < MAX_DIGITS) {
            get_value(ctx, depth + 1);
        } else {
            ctx->count++;
            int64_t v = 0;
            for (int i = 0; i < MAX_DIGITS; i++) {
                v = v * 10 + ctx->digits[i];
            }
            debug("[%d] %ld\n", ctx->count, v);
        }
        if (ctx->count == ctx->n) {
            return;
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = -1;

    ctx->count = -1;
    get_value(ctx, 0);

    int64_t v = -1;
    if (ctx->count == ctx->n) {
        v = 0;
        for (int i = 0; i < MAX_DIGITS; i++) {
            v = v * 10ULL + (int64_t)ctx->digits[i];
        }
    }

    printf("%ld\n", v);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
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
