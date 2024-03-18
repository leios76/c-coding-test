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
    int edge[1001][1032/32];
    int s[499501];
    int e[499501];
    int dfs_v[1001];
};
struct context_t context;

void dfs(struct context_t * ctx, int s)
{
    ctx->dfs_v[s] = 1;
    for (int b = 0; b <= ctx->n; b++) {
        if (ctx->edge[s][b/32] == 0) {
            b += 31;
            continue;
        }
        if (ctx->dfs_v[b] == 0 && (ctx->edge[s][b/32] & (1 << b))) {
            dfs(ctx, b);
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;
    for (int n = 1; n <= ctx->n; n++) {
        if (ctx->dfs_v[n] == 0) {
            result++;
            dfs(ctx, n);
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);

    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d", &ctx->s[m], &ctx->e[m]);
        ctx->edge[ctx->s[m]][ctx->e[m]/32] |= (1 << (ctx->e[m] % 32));
        ctx->edge[ctx->e[m]][ctx->s[m]/32] |= (1 << (ctx->s[m] % 32));
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
