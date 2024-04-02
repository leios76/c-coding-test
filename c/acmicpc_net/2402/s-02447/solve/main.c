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
};
struct context_t context;

void print_pattern(struct context_t * ctx, char ch, int i, int size)
{
    for (int j = 0; j < 3; j++) {
        if (((i / size) % 3) == 1 && j == 1) {
            if (size == 1) {
                printf(" ");
            } else {
                print_pattern(ctx, ' ', i, size / 3);
            }
        } else {
            if (size == 1) {
                printf("%c", ch);
            } else {
                print_pattern(ctx, ch, i, size / 3);
            }
        }
    }
    if (size == ctx->n / 3) {
        printf("\n");
    }
}

void solve(struct context_t * ctx)
{
    for (int n = 0; n < ctx->n; n++) {
        print_pattern(ctx, '*', n, ctx->n / 3);
    }
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
