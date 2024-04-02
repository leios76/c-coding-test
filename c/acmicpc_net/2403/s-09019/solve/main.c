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
    int op;
    int parent;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[10000];
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
    int a;
    int b;
    int bfs_v[10000];
    struct queue_t queue;
};

struct context_t context;

int calc(struct context_t * ctx, int t)
{
    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);

        if (index == t) {
            return index;
        }

        int v;
        v = (index * 2) % 10000;
        if (ctx->bfs_v[v] == 0) {
            debug("D index: %d -> %d\n", index, v);
            ctx->bfs_v[v] = 1;
            ctx->queue.queue_pool[v].parent = index;
            ctx->queue.queue_pool[v].op = 0;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
        }

        v = (index + 10000 - 1) % 10000;
        if (ctx->bfs_v[v] == 0) {
            debug("S index: %d -> %d\n", index, v);
            ctx->bfs_v[v] = 1;
            ctx->queue.queue_pool[v].parent = index;
            ctx->queue.queue_pool[v].op = 1;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
        }

        v = ((index * 10) % 10000) + (index / 1000);
        if (ctx->bfs_v[v] == 0) {
            debug("L index: %d -> %d\n", index, v);
            ctx->bfs_v[v] = 1;
            ctx->queue.queue_pool[v].parent = index;
            ctx->queue.queue_pool[v].op = 2;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
        }

        v = (index % 10) * 1000 + (int)(index / 10);
        if (ctx->bfs_v[v] == 0) {
            debug("R index: %d -> %d\n", index, v);
            ctx->bfs_v[v] = 1;
            ctx->queue.queue_pool[v].parent = index;
            ctx->queue.queue_pool[v].op = 3;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;
    char ops[4] = {'D', 'S', 'L', 'R'};
    int v;

    v = (ctx->a * 2) % 10000;
    if (ctx->bfs_v[v] == 0) {
        debug("D index: -1 -> %d\n", v);
        ctx->bfs_v[v] = 1;
        ctx->queue.queue_pool[v].parent = -1;
        ctx->queue.queue_pool[v].op = 0;
        insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
    }
    v = (ctx->a + 10000 - 1) % 10000;
    if (ctx->bfs_v[v] == 0) {
        debug("S index: -1 -> %d\n", v);
        ctx->bfs_v[v] = 1;
        ctx->queue.queue_pool[v].parent = -1;
        ctx->queue.queue_pool[v].op = 1;
        insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
    }

    v = ((ctx->a * 10) % 10000) + (ctx->a / 1000);
    if (ctx->bfs_v[v] == 0) {
        debug("L index: -1 -> %d\n", v);
        ctx->bfs_v[v] = 1;
        ctx->queue.queue_pool[v].parent = -1;
        ctx->queue.queue_pool[v].op = 2;
        insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
    }

    v = (ctx->a % 10) * 1000 + (int)(ctx->a / 10);
    if (ctx->bfs_v[v] == 0) {
        debug("R index: -1 -> %d\n", v);
        ctx->bfs_v[v] = 1;
        ctx->queue.queue_pool[v].parent = -1;
        ctx->queue.queue_pool[v].op = 3;
        insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, v);
    }
    int index = calc(ctx, ctx->b);
    char line[10001];
    int line_index = 10000;
    memset(line, 0, sizeof(line));
    debug("index: %d\n", index);
    while (index > -1) {
        debug(" index: %d, op: %d\n", index, ctx->queue.queue_pool[index].op);

        line[--line_index] = ops[ctx->queue.queue_pool[index].op];
        index = ctx->queue.queue_pool[index].parent;
    }
    printf("%s\n", &line[line_index]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    ctx->queue.queue_size = 0;
    scanf("%d", &ctx->a);
    scanf("%d", &ctx->b);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
