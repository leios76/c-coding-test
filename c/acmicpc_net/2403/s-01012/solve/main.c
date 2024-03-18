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
    int s;
    int g;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[2500];
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
    int k;
    int size[2500];
    int size_count;
    struct queue_t queue;
};
struct context_t context;

int set_group(struct context_t * ctx, int index)
{
    int x = index % 50;
    int y = index / 50;
    int count = 0;

    ctx->queue.queue_pool[index].g = ctx->size_count + 1;
    count++;
    if (x > 0) {
        if (ctx->queue.queue_pool[index - 1].g == -1 && ctx->queue.queue_pool[index - 1].s == 1) {
            count += set_group(ctx, index - 1);
        }
    }
    if (x < ctx->m - 1) {
        if (ctx->queue.queue_pool[index + 1].g == -1 && ctx->queue.queue_pool[index + 1].s == 1) {
            count += set_group(ctx, index + 1);
        }
    }
    if (y > 0) {
        if (ctx->queue.queue_pool[index - 50].g == -1 && ctx->queue.queue_pool[index - 50].s == 1) {
            count += set_group(ctx, index - 50);
        }
    }
    if (y < ctx->n - 1) {
        if (ctx->queue.queue_pool[index + 50].g == -1 && ctx->queue.queue_pool[index + 50].s == 1) {
            count += set_group(ctx, index + 50);
        }
    }
    return count;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);

        if (ctx->queue.queue_pool[index].g == -1 && ctx->queue.queue_pool[index].s == 1) {
            ctx->size[ctx->size_count++] = set_group(ctx, index);
        }
    }
    printf("%d\n", ctx->size_count);
}

void init_data(struct context_t * ctx)
{
    int x;
    int y;
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    ctx->queue.queue_size = 0;
    scanf("%d", &ctx->m);
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->k);
    for (int k = 0; k < ctx->k; k++) {
        scanf("%d%d", &x, &y);
        ctx->queue.queue_pool[y * 50 + x].s = 1;
        insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, y * 50 + x);
    }
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
