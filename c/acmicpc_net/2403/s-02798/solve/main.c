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
    int numbers[100];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int max_value = 0;
    for (int a = 0; a < ctx->n; a++) {
        for (int b = 0; b < ctx->n; b++) {
            for (int c = 0; c < ctx->n; c++) {
                if (a == b || b == c || a == c) {
                    continue;
                }
                if (ctx->numbers[a] + ctx->numbers[b] + ctx->numbers[c] <= ctx->m && max_value < ctx->numbers[a] + ctx->numbers[b] + ctx->numbers[c]) {
                    max_value = ctx->numbers[a] + ctx->numbers[b] + ctx->numbers[c];
                }
            }
        }
    }
    printf("%d\n", max_value);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->numbers[n]);
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
