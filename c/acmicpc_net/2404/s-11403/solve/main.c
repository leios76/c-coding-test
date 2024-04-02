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
    int dfs_v[128];
    int edge[128][128];
};
struct context_t context;

void dfs(struct context_t * ctx, int s)
{
    for (int b = 0; b < ctx->n; b++) {
        if (ctx->dfs_v[b] == 0 && (ctx->edge[s][b])) {
            ctx->dfs_v[b] = 1;
            dfs(ctx, b);
        }
    }
}


void solve(struct context_t * ctx)
{
    for (int r = 0; r < ctx->n; r++) {
        memset(ctx->dfs_v, 0, sizeof(ctx->dfs_v));
        dfs(ctx, r);
        for (int c = 0; c < ctx->n; c++) {
            printf("%d ", ctx->dfs_v[c]);
        }
        printf("\n");
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int r = 0; r < ctx->n; r++) {
        for (int c = 0; c < ctx->n; c++) {
            scanf("%d", &ctx->edge[r][c]);
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
