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
    int visited;
    int count;
    int map;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[2 * 1000 * 1000];
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
    struct queue_t queue;
};
struct context_t context;

int bfs(struct context_t * ctx)
{
    int dn[4] = {-1, 1, 0, 0};
    int dm[4] = {0, 0, -1, 1};
    int di[4] = {-1000, 1000, -1, 1};

    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);

        int n = (index / 1000) % 1000;
        int m = index % 1000;

        if (n == ctx->n - 1 && m == ctx->m - 1) {
            return ctx->queue.queue_pool[index].count;
        }

        for (int i = 0; i < 4; i++) {
            int nn = n + dn[i];
            int nm = m + dm[i];
            int b = index + di[i];
            if (nn >= 0 && nm >= 0 && nn < ctx->n && nm < ctx->m) {
                if (index < 1000000 && ctx->queue.queue_pool[b + 1000000].map == 1 && ctx->queue.queue_pool[b + 1000000].visited == 0) {
                    ctx->queue.queue_pool[b + 1000000].visited = 1;
                    ctx->queue.queue_pool[b + 1000000].count = ctx->queue.queue_pool[index].count + 1;
                    insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, b + 1000000);
                }
                if (ctx->queue.queue_pool[b].map == 0 && ctx->queue.queue_pool[b].visited == 0) {
                    ctx->queue.queue_pool[b].visited = 1;
                    ctx->queue.queue_pool[b].count = ctx->queue.queue_pool[index].count + 1;
                    insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, b);
                }
            }
        }
    }
    return -1;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    ctx->queue.queue_pool[0].count = 1;
    ctx->queue.queue_pool[0].visited = 1;
    ctx->queue.queue_pool[1000000].count = 1;
    ctx->queue.queue_pool[1000000].visited = 1;
    insert_queue(&ctx->queue, -1, -1, 0);

    result = bfs(ctx);

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    char line[1001];
    memset(ctx, 0, sizeof(struct context_t));
    ctx->queue.queue_head_index = -1;
    ctx->queue.queue_tail_index = -1;
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", line);
        for (int m = 0; m < ctx->m; m++) {
            if (line[m] == '1') {
                ctx->queue.queue_pool[n * 1000 + m].map = 1;
                ctx->queue.queue_pool[n * 1000 + m + 1000000].map = 1;
            }
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
