#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif


struct queue_entity_t {
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[1001];
    int queue_head_index;
    int queue_tail_index;
    int queue_size;
};

void remove_queue(struct queue_t * queue, int index)
{
    queue->queue_size--;
    if (index == queue->queue_tail_index) {
        #ifdef DEBUG_QUEUE
        debug("update tail index: %d -> %d\n", queue->queue_tail_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_tail_index = queue->queue_pool[index].prev_index;
    }
    if (index == queue->queue_head_index) {
        #ifdef DEBUG_QUEUE
        debug("update head index: %d -> %d\n", queue->queue_head_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_head_index = queue->queue_pool[index].next_index;
    }

    if (queue->queue_pool[index].prev_index != -1) {
        #ifdef DEBUG_QUEUE
        debug("update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].prev_index].next_index = queue->queue_pool[index].next_index;
    }
    if (queue->queue_pool[index].next_index != -1) {
        #ifdef DEBUG_QUEUE
        debug("update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].next_index].prev_index = queue->queue_pool[index].prev_index;
    }
}

void insert_queue(struct queue_t * queue, int after, int before, int index)
{
    queue->queue_size++;
    if (queue->queue_head_index == -1 && queue->queue_tail_index == -1) {
        #ifdef DEBUG_QUEUE
        debug("update head index: %d -> %d\n", queue->queue_head_index, index);
        #endif
        queue->queue_head_index = index;
        #ifdef DEBUG_QUEUE
        debug("update tail index: %d -> %d\n", queue->queue_tail_index, index);
        #endif
        queue->queue_tail_index = index;
        queue->queue_pool[index].prev_index = -1;
        queue->queue_pool[index].next_index = -1;
    } else {
        if (after != -1) {
            #ifdef DEBUG_QUEUE
            debug("update next index (%d): %d -> %d\n", index, -1, queue->queue_pool[after].next_index);
            #endif
            queue->queue_pool[index].next_index = queue->queue_pool[after].next_index;
            #ifdef DEBUG_QUEUE
            debug("update next index (%d): %d -> %d\n", after, queue->queue_pool[after].next_index, index);
            #endif
            queue->queue_pool[after].next_index = index;
            #ifdef DEBUG_QUEUE
            debug("update prev index (%d): %d -> %d\n", index, queue->queue_pool[after].prev_index, after);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_tail_index;
            if (after == queue->queue_tail_index) {
                #ifdef DEBUG_QUEUE
                debug("update tail index: %d -> %d\n", queue->queue_tail_index, index);
                #endif
                queue->queue_tail_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug("update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].next_index].prev_index = index;
            }
        } else if (before != -1) {
            #ifdef DEBUG_QUEUE
            debug("update prev index (%d): %d -> %d\n", index, -1, queue->queue_pool[before].prev_index);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_pool[before].prev_index;
            #ifdef DEBUG_QUEUE
            debug("update prev index (%d): %d -> %d\n", before, queue->queue_pool[before].prev_index, index);
            #endif
            queue->queue_pool[before].prev_index = index;
            #ifdef DEBUG_QUEUE
            debug("update next index (%d): %d -> %d\n", index, queue->queue_pool[index].next_index, before);
            #endif
            queue->queue_pool[index].next_index = before;
            if (before == queue->queue_head_index) {
                #ifdef DEBUG_QUEUE
                debug("update head index: %d -> %d\n", queue->queue_head_index, index);
                #endif
                queue->queue_head_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug("update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].prev_index].next_index = index;
            }
        }
    }
}

struct context_t {
    int n;
    int m;
    int v;
    int edge[1001][1032 / 32];
    int s[10001];
    int e[10001];
    int dfs_v[1001];
    int bfs_v[1001];

    struct queue_t queue;
};
struct context_t context;

void dfs(struct context_t * ctx, int s)
{
    printf("%d ", s);
    for (int m = 0; m < ctx->m; m++) {
        ctx->dfs_v[s] = 1;
        for (int b = 0; b <= ctx->n; b++) {
            if (ctx->edge[s][b / 32] == 0) {
                b += 31;
                continue;
            }
            if (ctx->dfs_v[b] == 0 && (ctx->edge[s][b / 32] & (1 << b))) {
                dfs(ctx, b);
            }
        }
    }
}

void bfs(struct context_t * ctx)
{
    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        printf("%d ", index);
        remove_queue(&ctx->queue, index);
        ctx->bfs_v[index] = 1;

        for (int b = 0; b <= ctx->n; b++) {
            if (ctx->edge[index][b / 32] == 0) {
                b += 31;
                continue;
            }
            if (ctx->bfs_v[b] == 0 && (ctx->edge[index][b / 32] & (1 << b))) {
                insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, b);
                ctx->bfs_v[b] = 1;
            }
        }
    }
}

void solve(struct context_t * ctx)
{
    dfs(ctx, ctx->v);
    printf("\n");

    insert_queue(&ctx->queue, -1, -1, ctx->v);
    bfs(ctx);
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    ctx->queue.queue_size = 0;
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    scanf("%d", &ctx->v);

    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d", &ctx->s[m], &ctx->e[m]);
        ctx->edge[ctx->s[m]][ctx->e[m] / 32] |= (1 << (ctx->e[m] % 32));
        ctx->edge[ctx->e[m]][ctx->s[m] / 32] |= (1 << (ctx->s[m] % 32));
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
