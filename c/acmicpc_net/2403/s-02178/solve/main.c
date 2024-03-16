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
    int t;
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
    int n;
    int m;
    struct queue_t queue;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int start_n = 0;
    int start_m = 0;

    ctx->queue.queue_pool[0].s = 0;
    ctx->queue.queue_pool[0].t = 1;
    insert_queue(&ctx->queue, -1, -1, 0);

    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);

        int n = index / 100;
        int m = index % 100;
        debug("remove %d,%d\n", n, m);
        if (n > 0 && ctx->queue.queue_pool[index - 100].s == 1) {
            ctx->queue.queue_pool[index - 100].s = 0;
            ctx->queue.queue_pool[index - 100].t = ctx->queue.queue_pool[index].t + 1;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index - 100);
            debug("add %d,%d %d\n", n - 1, m, ctx->queue.queue_pool[index - 100].t);
        }
        if (n + 1 < ctx->n && ctx->queue.queue_pool[index + 100].s == 1) {
            ctx->queue.queue_pool[index + 100].s = 0;
            ctx->queue.queue_pool[index + 100].t = ctx->queue.queue_pool[index].t + 1;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index + 100);
            debug("add %d,%d %d\n", n + 1, m, ctx->queue.queue_pool[index + 100].t);
        }
        if (m > 0 && ctx->queue.queue_pool[index - 1].s == 1) {
            ctx->queue.queue_pool[index - 1].s = 0;
            ctx->queue.queue_pool[index - 1].t = ctx->queue.queue_pool[index].t + 1;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index - 1);
            debug("add %d,%d %d\n", n, m - 1, ctx->queue.queue_pool[index - 1].t);
        }
        if (m + 1 < ctx->m && ctx->queue.queue_pool[index + 1].s == 1) {
            ctx->queue.queue_pool[index + 1].s = 0;
            ctx->queue.queue_pool[index + 1].t = ctx->queue.queue_pool[index].t + 1;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, index + 1);
            debug("add %d,%d %d\n", n, m + 1, ctx->queue.queue_pool[index + 1].t);
        }
    }

    printf("%d\n", ctx->queue.queue_pool[(ctx->n - 1) * 100 + ctx->m - 1].t);
}

void init_data(struct context_t * ctx)
{
    char line[101];
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    ctx->queue.queue_size = 0;

    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", line);
        for (int m = 0; m < ctx->m; m++) {
            ctx->queue.queue_pool[n * 100 + m].s = line[m] - '0';
            debug("set %d,%d => %d\n", n, m, ctx->queue.queue_pool[n * 100 + m].s = line[m] - '0');
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
