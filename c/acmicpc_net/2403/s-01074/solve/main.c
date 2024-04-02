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
    int r;
    int c;
};
struct context_t context;

int get_pos(int n, int r, int c)
{
    int half = (1 << n) / 2;
    int rs = r / half;
    int cs = c / half;
    debug("[n %d] [half %d] [rs %d] [cs %d]\n", n, half, rs, cs);
    if (n == 1) {
        return rs * 2 + cs;
    } else {
        return (2 * rs + cs) * (half * half) + get_pos(n - 1, r % half, c % half);
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;

    result = get_pos(ctx->n, ctx->r, ctx->c);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->r);
    scanf("%d", &ctx->c);
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
