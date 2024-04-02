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
    int result = 0;
    int depth = 0;
    int start = 1;
    int end = 7;
    int distance = 6;
    if (ctx->n == 1) {
        printf("%d\n", 1);
        return;
    }
    while (1) {
        debug("[%3d] %d ~ %d\n", depth, start, end);
        if (start < ctx->n && ctx->n <= end) {
            printf("%d\n", depth + 2);
            return;
        }
        depth++;
        distance += 6;
        start = end;
        end = end + distance;
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
