#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
    //#define DEBUG_QUEUE
#else
    #define debug(...)
#endif

struct queue_entity_t {
    int available;
    int n;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[100001];
    int queue_head_index;
    int queue_tail_index;
};

struct context_t {
    uint32_t n;
    uint32_t k;

    int time_spent[100001];

    struct queue_t queue;
};
struct context_t context;


void remove_queue(struct queue_t * queue, int index)
{
    debug("remove queue: %d\n", index);
    queue->queue_pool[index].available = -1;
    if (index == queue->queue_tail_index) {
        #ifdef DEBUG_QUEUE
        debug("  update tail index: %d -> %d\n", queue->queue_tail_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_tail_index = queue->queue_pool[index].prev_index;
    }
    if (index == queue->queue_head_index) {
        #ifdef DEBUG_QUEUE
        debug("  update head index: %d -> %d\n", queue->queue_head_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_head_index = queue->queue_pool[index].next_index;
    }

    if (queue->queue_pool[index].prev_index != -1) {
        #ifdef DEBUG_QUEUE
        debug("  update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].prev_index].next_index = queue->queue_pool[index].next_index;
    }
    if (queue->queue_pool[index].next_index != -1) {
        #ifdef DEBUG_QUEUE
        debug("  update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].next_index].prev_index = queue->queue_pool[index].prev_index;
    }
}

void insert_queue(struct queue_t * queue, int after, int before, int index)
{
    debug("insert queue %d / %d / %d\n", before, index, after);
    queue->queue_pool[index].available = 0;
    if (queue->queue_head_index == -1 && queue->queue_tail_index == -1) {
        #ifdef DEBUG_QUEUE
        debug("  update head index: %d -> %d\n", queue->queue_head_index, index);
        #endif
        queue->queue_head_index = index;
        #ifdef DEBUG_QUEUE
        debug("  update tail index: %d -> %d\n", queue->queue_tail_index, index);
        #endif
        queue->queue_tail_index = index;
        queue->queue_pool[index].prev_index = -1;
        queue->queue_pool[index].next_index = -1;
    } else {
        if (after != -1) {
            #ifdef DEBUG_QUEUE
            debug("  update next index (%d): %d -> %d\n", index, -1, queue->queue_pool[after].next_index);
            #endif
            queue->queue_pool[index].next_index = queue->queue_pool[after].next_index;
            #ifdef DEBUG_QUEUE
            debug("  update next index (%d): %d -> %d\n", after, queue->queue_pool[after].next_index, index);
            #endif
            queue->queue_pool[after].next_index = index;
            #ifdef DEBUG_QUEUE
            debug("  update prev index (%d): %d -> %d\n", index, queue->queue_pool[after].prev_index, after);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_tail_index;
            if (after == queue->queue_tail_index) {
                #ifdef DEBUG_QUEUE
                debug("  update tail index: %d -> %d\n", queue->queue_tail_index, index);
                #endif
                queue->queue_tail_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug("  update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].next_index].prev_index = index;
            }
        } else if (before != -1) {
            #ifdef DEBUG_QUEUE
            debug("  update prev index (%d): %d -> %d\n", index, -1, queue->queue_pool[before].prev_index);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_pool[before].prev_index;
            #ifdef DEBUG_QUEUE
            debug("  update prev index (%d): %d -> %d\n", before, queue->queue_pool[before].prev_index, index);
            #endif
            queue->queue_pool[before].prev_index = index;
            #ifdef DEBUG_QUEUE
            debug("  update next index (%d): %d -> %d\n", index, queue->queue_pool[index].next_index, before);
            #endif
            queue->queue_pool[index].next_index = before;
            if (before == queue->queue_head_index) {
                #ifdef DEBUG_QUEUE
                debug("  update head index: %d -> %d\n", queue->queue_head_index, index);
                #endif
                queue->queue_head_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug("  update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].prev_index].next_index = index;
            }
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;
    int n;
    ctx->time_spent[ctx->n] = 0;
    ctx->queue.queue_pool[ctx->n].n = ctx->n;
    ctx->queue.queue_pool[ctx->n].available = 0;
    ctx->queue.queue_head_index = ctx->n;
    ctx->queue.queue_tail_index = ctx->n;


    while (ctx->queue.queue_head_index != -1 || ctx->queue.queue_tail_index != -1) {
        int index = -1;
        debug("Checking index %d %d\n", ctx->queue.queue_head_index, ctx->queue.queue_tail_index);

        if (ctx->queue.queue_head_index != -1) {
            index = ctx->queue.queue_head_index;
            remove_queue(&ctx->queue, ctx->queue.queue_head_index);
        }

        if (index == -1) {
            continue;
        }

        n = ctx->queue.queue_pool[index].n;
        debug("Checking point %d\n", n);

        if (n == ctx->k) {
            printf("%d\n", ctx->time_spent[ctx->k]);
            return;
        }

        if (n > 0) {
            if (ctx->time_spent[n - 1] == -1 || ctx->time_spent[n - 1] > ctx->time_spent[n] + 1) {
                debug("update point %d time_spent %d -> %d\n", n - 1, ctx->time_spent[n - 1], ctx->time_spent[n] + 1);
                ctx->time_spent[n - 1] = ctx->time_spent[n] + 1;
                ctx->queue.queue_pool[n - 1].n = n - 1;
                if (ctx->queue.queue_pool[n - 1].available == -1) {
                    insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, n - 1);
                }
            }
        }

        if (n < ctx->k && n + 1 <= 100000) {
            if (ctx->time_spent[n + 1] == -1 || ctx->time_spent[n + 1] > ctx->time_spent[n] + 1) {
                debug("update point %d time_spent %d -> %d\n", n + 1, ctx->time_spent[n + 1], ctx->time_spent[n] + 1);
                ctx->time_spent[n + 1] = ctx->time_spent[n] + 1;
                ctx->queue.queue_pool[n + 1].n = n + 1;
                if (ctx->queue.queue_pool[n + 1].available == -1) {
                    insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, n + 1);
                }
            }
        }

        if (n < ctx->k && n * 2 <= 100000 && n != 0) {
            if (ctx->time_spent[n * 2] == -1 || ctx->time_spent[n * 2] > ctx->time_spent[n]) {
                debug("update point %d time_spent %d -> %d\n", n * 2, ctx->time_spent[n * 2], ctx->time_spent[n]);
                ctx->time_spent[n * 2] = ctx->time_spent[n];
                ctx->queue.queue_pool[n * 2].n = n * 2;
                if (ctx->queue.queue_pool[n * 2].available == -1) {
                    insert_queue(&ctx->queue, -1, ctx->queue.queue_head_index, n * 2);
                }
            }
        }
    }
        debug("Checking index %d, %d\n", ctx->queue.queue_head_index, ctx->queue.queue_tail_index);

    printf("%d\n", ctx->time_spent[ctx->k]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->k);
    memset(ctx->time_spent, 0xFF, sizeof(ctx->time_spent));
    memset(&ctx->queue, 0xFF, sizeof(ctx->queue));
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
