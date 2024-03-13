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
    int c;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[512*512];
    int queue_head_index[257];
    int queue_tail_index[257];
    int queue_size[257];
};

void remove_queue(struct queue_t * queue, int queue_index, int index)
{
    queue->queue_size[queue_index]--;
    if (index == queue->queue_tail_index[queue_index]) {
        #ifdef DEBUG_QUEUE
        debug("update tail index: %d -> %d\n", queue->queue_tail_index[queue_index], queue->queue_pool[index].prev_index);
        #endif
        queue->queue_tail_index[queue_index] = queue->queue_pool[index].prev_index;
    }
    if (index == queue->queue_head_index[queue_index]) {
        #ifdef DEBUG_QUEUE
        debug("update head index: %d -> %d\n", queue->queue_head_index[queue_index], queue->queue_pool[index].next_index);
        #endif
        queue->queue_head_index[queue_index] = queue->queue_pool[index].next_index;
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

void insert_queue(struct queue_t * queue, int queue_index, int after, int before, int index)
{
    queue->queue_size[queue_index]++;
    if (queue->queue_head_index[queue_index] == -1 && queue->queue_tail_index[queue_index] == -1) {
        #ifdef DEBUG_QUEUE
        debug("update head index: %d -> %d\n", queue->queue_head_index[queue_index], index);
        #endif
        queue->queue_head_index[queue_index] = index;
        #ifdef DEBUG_QUEUE
        debug("update tail index: %d -> %d\n", queue->queue_tail_index[queue_index], index);
        #endif
        queue->queue_tail_index[queue_index] = index;
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
            queue->queue_pool[index].prev_index = queue->queue_tail_index[queue_index];
            if (after == queue->queue_tail_index[queue_index]) {
                #ifdef DEBUG_QUEUE
                debug("update tail index: %d -> %d\n", queue->queue_tail_index[queue_index], index);
                #endif
                queue->queue_tail_index[queue_index] = index;
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
            if (before == queue->queue_head_index[queue_index]) {
                #ifdef DEBUG_QUEUE
                debug("update head index: %d -> %d\n", queue->queue_head_index[queue_index], index);
                #endif
                queue->queue_head_index[queue_index] = index;
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
    int b;
    struct queue_t queue;
};
struct context_t context;

int find_min_height(struct queue_t * queue)
{
    return -1;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    int min_height;
    int max_height;
    int fill_time;
    int dig_time;
    int index;
    while (1) {
        for (int i = 0; i < 257; i++) {
            if (ctx->queue.queue_size[i] > 0) {
                min_height = i;
                break;
            }
        }
        for (int i = 256; i >= 0; i--) {
            if (ctx->queue.queue_size[i] > 0) {
                max_height = i;
                break;
            }
        }
        if (min_height == max_height) {
            break;
        }

        if (ctx->queue.queue_size[min_height] > ctx->b) {
            while (ctx->queue.queue_size[max_height] > 0 && ctx->queue.queue_size[min_height] > ctx->b) {
                index = ctx->queue.queue_head_index[max_height];
                remove_queue(&ctx->queue, max_height, index);
                ctx->b++;
                insert_queue(&ctx->queue, max_height - 1, ctx->queue.queue_tail_index[max_height - 1], -1, index);
                result += 2;
            }
            continue;
        }
        fill_time = ctx->queue.queue_size[min_height];
        dig_time = ctx->queue.queue_size[max_height] * 2;

        if (fill_time <= dig_time) {
            while (ctx->b > 0 && ctx->queue.queue_size[min_height] > 0) {
                index = ctx->queue.queue_head_index[min_height];
                remove_queue(&ctx->queue, min_height, index);
                ctx->b--;
                insert_queue(&ctx->queue, min_height + 1, ctx->queue.queue_tail_index[min_height + 1], -1, index);
                result++;
            }
            while (ctx->queue.queue_size[min_height] > 0) {
                index = ctx->queue.queue_head_index[max_height];
                remove_queue(&ctx->queue, max_height, index);
                ctx->b++;
                insert_queue(&ctx->queue, max_height - 1, ctx->queue.queue_tail_index[max_height - 1], -1, index);
                result += 2;

                index = ctx->queue.queue_head_index[min_height];
                remove_queue(&ctx->queue, min_height, index);
                ctx->b--;
                insert_queue(&ctx->queue, min_height + 1, ctx->queue.queue_tail_index[min_height + 1], -1, index);
                result++;
            }
        } else {
            while (ctx->queue.queue_size[max_height] > 0) {
                index = ctx->queue.queue_head_index[max_height];
                remove_queue(&ctx->queue, max_height, index);
                ctx->b++;
                insert_queue(&ctx->queue, max_height - 1, ctx->queue.queue_tail_index[max_height - 1], -1, index);
                result += 2;
            }
        }
    }

    printf("%d %d\n", result, max_height);
}

void init_data(struct context_t * ctx)
{
    int h;
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    memset(ctx->queue.queue_size, 0, sizeof(ctx->queue.queue_size));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    scanf("%d", &ctx->b);
    for (int n = 0; n < ctx->n; n++) {
        for (int m = 0; m < ctx->m; m++) {
            scanf("%d", &h);
            insert_queue(&ctx->queue, h, ctx->queue.queue_tail_index[h], -1, n << 9 | m);
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
