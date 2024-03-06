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
    int numbers[100];
};
struct context_t context;

int check_number(int n)
{
    if (n == 1) {
        return 0;
    }
    for (int i = 2; i < n; i++) {
        if ((n % i) == 0) {
            return 0;
        }
    }
    return 1;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    for (int n = 0; n < ctx->n; n++) {
        result += check_number(ctx->numbers[n]);
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
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
