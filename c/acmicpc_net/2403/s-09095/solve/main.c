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

int get_count(int n, int t)
{
    int count = 0;
    if (n == t) {
        return 1;
    }
    if (n + 1 <= t) {
        count += get_count(n + 1, t);
    }
    if (n + 2 <= t) {
        count += get_count(n + 2, t);
    }
    if (n + 3 <= t) {
        count += get_count(n + 3, t);
    }
    return count;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    printf("%d\n", get_count(0, ctx->n));
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
