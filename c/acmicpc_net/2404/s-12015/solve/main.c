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
    int v[1000000];
    int buffer[1000000];
    int buffer_size;
};
struct context_t context;

int binary_lower_bound(int number, int arr[], int left, int right)
{
    int s = 0;
    int e = right;

    while (s < e) {
        int d = (e + s) / 2;

        if (number > arr[d]) {
            s = d + 1;
        } else {
            e = d;
        }
    }
    return e;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    ctx->buffer[0] = ctx->v[0];
    ctx->buffer_size++;
    for (int n = 1; n < ctx->n; n++) {
        if (ctx->buffer[ctx->buffer_size - 1] < ctx->v[n]) {
            ctx->buffer[ctx->buffer_size++] = ctx->v[n];
        } else {
            int index = binary_lower_bound(ctx->v[n], ctx->buffer, 0, ctx->buffer_size - 1);
            ctx->buffer[index] = ctx->v[n];
        }
    }
    printf("%d\n", ctx->buffer_size);
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
