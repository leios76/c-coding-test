#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

int running = 1;
struct context_t {
    int n;
    int8_t digits[5];
    int length;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 1;
    if (ctx->n == 0) {
        running = 0;
        return;
    }
    memset(ctx->digits, -1, sizeof(ctx->digits));
    int n = ctx->n;
    while (n > 0) {
        ctx->digits[ctx->length++] = n % 10;
        n = n / 10;
    }
    debug("number %d, length: %d, digits %d %d %d %d %d\n", ctx->n, ctx->length, ctx->digits[4], ctx->digits[3], ctx->digits[2], ctx->digits[1], ctx->digits[0]);

    for (int l = 0; l < ctx->length; l++) {
        if (ctx->digits[l] != ctx->digits[ctx->length - l - 1]) {
            result = 0;
            break;
        }
    }
    printf("%s\n", result ? "yes":"no");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
}

int main(int argc, char ** argv)
{
    //scanf("%d", &t);
    while (running) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
