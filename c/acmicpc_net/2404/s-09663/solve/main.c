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
    int queen_x[15];
};
struct context_t context;

static inline int available(struct context_t * ctx, int tx, int count)
{
    for (int n = 0; n < count; n++) {
        if (ctx->queen_x[n] == tx) {
            return 0;
        }
        if (abs(ctx->queen_x[n] - tx) == count - n) {
            return 0;
        }
    }
    return 1;
}

int r(struct context_t * ctx, int offset, int depth)
{
    int count = 0;
    for (int x = 0; x < ctx->n; x++) {
        if (available(ctx, x, depth)) {
            ctx->queen_x[depth] = x;
            if (depth < ctx->n - 1) {
                count += r(ctx, x, depth + 1);
            } else {
                count++;
            }
        }
    }
    return count;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = r(ctx, 0, 0);
    printf("%d\n", result);
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
