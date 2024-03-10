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

int count6(int n)
{
    int c = 0;
    while (n > 0) {
        if ((n % 10) == 6) {
            c++;
        } else if (c > 0) {
            c = 0;
        }
        if (c >= 3) {
            break;
        }
        n = n / 10;
    }
    return c;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    int n = 0;
    while (1) {
        if (count6(result) >= 3) {
            n++;
            if (n == ctx->n) {
                break;
            }
        }
        result++;

    }
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
