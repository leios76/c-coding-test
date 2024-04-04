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
    struct queue_entity_t queue_pool[64];
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
    int wall[3];
    int count;

    int bfs_v[64];
    struct queue_t queue;

    int init_bfs_v[64];
    struct queue_t init_queue;
};
struct context_t context;

void bfs(struct context_t * ctx)
{
    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);

        int x = index % 8;
        int y = index / 8;

        if (x > 0) {
            if (ctx->bfs_v[index - 1] == 0) {
                insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index - 1);
                ctx->bfs_v[index - 1] = 2;
            }
        }
        if (y > 0) {
            if (ctx->bfs_v[index - 8] == 0) {
                insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index - 8);
                ctx->bfs_v[index - 8] = 2;
            }
        }
        if (x < ctx->m -  1) {
            if (ctx->bfs_v[index + 1] == 0) {
                insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index + 1);
                ctx->bfs_v[index + 1] = 2;
            }
        }
        if (y < ctx->n - 1) {
            if (ctx->bfs_v[index + 8] == 0) {
                insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index + 8);
                ctx->bfs_v[index + 8] = 2;
            }
        }
    }
}

int get_count(struct context_t * ctx)
{
    int count = 0;

    memcpy(ctx->bfs_v, ctx->init_bfs_v, sizeof(ctx->bfs_v));
    memcpy(&ctx->queue, &ctx->init_queue, sizeof(ctx->queue));

    for (int i = 0; i < 3; i++) {
        if (ctx->wall[i] > -1) {
            ctx->bfs_v[ctx->wall[i]] = 1;
        }
    }

    bfs(ctx);
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            if (ctx->bfs_v[n*8 + m] == 0) {
                count++;
            }
        }
    }


    return count;
}

int r(struct context_t * ctx, int offset, int depth)
{
    int count;
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            if (offset > 0) {
                n = offset / 8;
                m = offset % 8;
                offset = 0;
                continue;
            }
            if (ctx->init_bfs_v[n*8 + m] == 0) {
                ctx->wall[depth] = n*8 + m;
                if (depth < 2) {
                    r(ctx, n*8 + m, depth + 1);
                } else {
                    count = get_count(ctx);
                    if (ctx->count < count) {
                        ctx->count = count;
                    }
                }
            }
        }
    }
    return ctx->count;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = r(ctx, 0, 0);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    ctx->init_queue.queue_head_index = -1;
    ctx->init_queue.queue_tail_index = -1;
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            scanf("%d", &ctx->init_bfs_v[n*8 + m]);
            if (ctx->init_bfs_v[n*8 + m] == 2) {
                insert_queue(&ctx->init_queue, ctx->init_queue.queue_tail_index, -1, n*8 + m);
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
