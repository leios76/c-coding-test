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

void solve(struct context_t * ctx)
{
    uint64_t result = 1;
    int zero_count = 0;
    for (int n = ctx->n; n > 0; n--) {
        result = result * n;
        while (result > 10 && result % 10 == 0) {
            zero_count++;
            result = result / 10;
        }
        result = result % 10000;
    }
    printf("%d\n", zero_count);
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
