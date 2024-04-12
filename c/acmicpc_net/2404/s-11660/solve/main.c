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
    int sum_table[1025][1025];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int x1;
    int y1;
    int x2;
    int y2;

    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d%d%d", &y1, &x1, &y2, &x2);
        result = 0;
        for (int y = y1; y <= y2; y++) {
            result += (ctx->sum_table[y][x2] - ctx->sum_table[y][x1 - 1]);
        }
        printf("%d\n", result);
    }
}

void init_data(struct context_t * ctx)
{
    int v;
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int ny = 1; ny <= ctx->n; ny++) {
        for (int nx = 1; nx <= ctx->n; nx++) {
            scanf("%d", &v);
            ctx->sum_table[ny][nx] = ctx->sum_table[ny][nx - 1] + v;
        }
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
