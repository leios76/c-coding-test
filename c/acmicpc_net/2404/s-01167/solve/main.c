#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct link_t {
    int to;
    int distance;
    int next_index;
};

struct node_t {
    int next_index;
    int link_head_index;
    int link_tail_index;
};

struct context_t {
    int v;
    int link_count;

    int dfs_v[100001];
    struct node_t node_pool[100001];
    struct link_t link_pool[200002];
};
struct context_t context;

int dfs(struct context_t * ctx, int s)
{
    int max_distance = 0;
    int distance;
    int node_index;
    int link_index;

    link_index = ctx->node_pool[s].link_head_index;

    while (link_index != -1) {
        if (ctx->dfs_v[ctx->link_pool[link_index].to] == 0) {
            ctx->dfs_v[ctx->link_pool[link_index].to] = 1;
            distance = ctx->link_pool[link_index].distance + dfs(ctx, ctx->link_pool[link_index].to);
            if (max_distance < distance) {
                max_distance = distance;
                ctx->node_pool[s].next_index = ctx->link_pool[link_index].to;
            }

        }
        link_index = ctx->link_pool[link_index].next_index;
    }

    return max_distance;
}

void solve(struct context_t * ctx)
{
    int max_result = 0;
    int result = 0;

    int start_pos = 1;
    int pos;

    for (int i = 0; i < 2; i++) {
        memset(ctx->dfs_v, 0, sizeof(ctx->dfs_v));
        ctx->dfs_v[start_pos] = 1;
        result = dfs(ctx, start_pos);
        if (max_result < result) {
            max_result = result;
        }

        if (i == 0) {
            pos = start_pos;
            while (pos != -1) {
                pos = ctx->node_pool[pos].next_index;
                if (pos != -1) {
                    start_pos = pos;
                }
            }
        }
    }

    printf("%d\n", max_result);
}

void init_data(struct context_t * ctx)
{
    int n;
    int to;
    int dist;
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->link_pool, -1, sizeof(ctx->link_pool));
    memset(ctx->node_pool, -1, sizeof(ctx->node_pool));
    scanf("%d", &ctx->v);
    for (int v = 1; v <= ctx->v; v++) {
        scanf("%d", &n);
        while (1) {
            scanf("%d", &ctx->link_pool[ctx->link_count].to);
            if (ctx->link_pool[ctx->link_count].to == -1) {
                break;
            }
            scanf("%d", &ctx->link_pool[ctx->link_count].distance);

            if (ctx->node_pool[n].link_head_index == -1) {
                ctx->node_pool[n].link_head_index = ctx->link_count;
                ctx->node_pool[n].link_tail_index = ctx->link_count;
            } else {
                ctx->link_pool[ctx->node_pool[n].link_tail_index].next_index = ctx->link_count;
                ctx->node_pool[n].link_tail_index = ctx->link_count;
            }
            ctx->link_count++;
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
