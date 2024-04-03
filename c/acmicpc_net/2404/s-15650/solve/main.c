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
    int dfs_v[9];
    int values[9];
};
struct context_t context;

void dfs(struct context_t * ctx, int s, int depth)
{
    if (depth > ctx->m) {
        for (int m = 1; m <= ctx->m; m++) {
            printf("%d ", ctx->values[m]);
        }
        printf("\n");
        return;
    }
    for (int n = 1; n <= ctx->n; n++) {
        if (ctx->dfs_v[n] == 0 && ctx->values[depth - 1] < n) {
            ctx->dfs_v[n] = 1;
            ctx->values[depth] = n;
            dfs(ctx, n, depth + 1);
            ctx->dfs_v[n] = 0;
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;
    memset(ctx->dfs_v, 0, sizeof(ctx->dfs_v));
    dfs(ctx, 1, 1);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
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
