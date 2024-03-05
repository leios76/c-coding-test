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
    int c[100000];
    int a[100000];
    int b[100000];
    int group[1000001];
};
struct context_t context;


int find_parent(struct context_t * c, int x)
{
    if (c->group[x] == x) {
        return x;
    }
    c->group[x] = find_parent(c, c->group[x]);
    return c->group[x];
}

int union_parent(struct context_t * c, int a, int b)
{
    int root_a = find_parent(c, a);
    int root_b = find_parent(c, b);

    if (root_b != root_a) {
        if (root_b < root_a) {
            c->group[root_a] = root_b;
        } else {
            c->group[root_b] = root_a;
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n = 0; n <= ctx->n; n++) {
        ctx->group[n] = n;
    }

    for (int m = 0; m < ctx->m; m++) {
        if (ctx->c[m] == 0) {
            union_parent(ctx, ctx->a[m], ctx->b[m]);
        } else {
            int root_a = find_parent(ctx, ctx->a[m]);
            int root_b = find_parent(ctx, ctx->b[m]);
            if (root_a == root_b) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);

    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d%d", &ctx->c[m], &ctx->a[m], &ctx->b[m]);
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
