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
    int top[3];
};
struct context_t context;

void hanoi(struct context_t * ctx, int count, int start, int end, int via)
{
    if (count > 1) {
        hanoi(ctx, count - 1, start, via, end);
    }
    printf("%d %d\n", start + 1, end + 1);
    ctx->top[end] = ctx->top[start];
    ctx->top[start]++;

    if (count > 1) {
        hanoi(ctx, count - 1, via, end, start);
    }
}

void solve(struct context_t * ctx)
{
    int count = 0;
    for (int n = 0; n < ctx->n; n++) {
        count = count * 2 + 1;
    }
    printf("%d\n", count);
    ctx->top[0] = 1;
    ctx->top[1] = 0;
    ctx->top[2] = 0;
    hanoi(ctx, ctx->n, 0, 2, 1);
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
