#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif


#define MAX_QUEUE_SIZE      1000000

struct queue_entity_t {
    int n;
    int turn;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[MAX_QUEUE_SIZE];
    int queue_head_index;
    int queue_tail_index;
    int queue_size;
    int queue_index;
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
    struct queue_t queue;
};
struct context_t context;

int bfs(struct context_t * ctx)
{
    int checked_turn = 0;
    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);
        debug("check [%d](n %d)(turn %d) - %d\n", index, ctx->queue.queue_pool[index].n, ctx->queue.queue_pool[index].turn, ctx->b);

        if (ctx->queue.queue_pool[index].n == ctx->a) {
            return ctx->queue.queue_pool[index].turn + 1;
        }

        if ((ctx->queue.queue_pool[index].n & 0x01) == 0x00 && (ctx->queue.queue_pool[index].n / 2) >= ctx->a) {
            ctx->queue.queue_pool[ctx->queue.queue_index].n = ctx->queue.queue_pool[index].n / 2;
            ctx->queue.queue_pool[ctx->queue.queue_index].turn = ctx->queue.queue_pool[index].turn + 1;
            debug("add queue[%d] %d turn %d\n", ctx->queue.queue_index, ctx->queue.queue_pool[ctx->queue.queue_index].n, ctx->queue.queue_pool[ctx->queue.queue_index].turn);
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, ctx->queue.queue_index);
            ctx->queue.queue_index = (ctx->queue.queue_index + 1) % MAX_QUEUE_SIZE;
        }

        if ((ctx->queue.queue_pool[index].n % 10) == 1 && (ctx->queue.queue_pool[index].n / 10) >= ctx->a) {
            ctx->queue.queue_pool[ctx->queue.queue_index].n = ctx->queue.queue_pool[index].n / 10;
            ctx->queue.queue_pool[ctx->queue.queue_index].turn = ctx->queue.queue_pool[index].turn + 1;
            debug("add queue[%d] %d turn %d\n", ctx->queue.queue_index, ctx->queue.queue_pool[ctx->queue.queue_index].n, ctx->queue.queue_pool[ctx->queue.queue_index].turn);
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, ctx->queue.queue_index);
            ctx->queue.queue_index = (ctx->queue.queue_index + 1) % MAX_QUEUE_SIZE;
        }
    }
    return -1;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    ctx->queue.queue_pool[ctx->queue.queue_index].n = ctx->b;
    ctx->queue.queue_pool[ctx->queue.queue_index].turn = 0;
    insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, ctx->queue.queue_index++);

    result = bfs(ctx);

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    ctx->queue.queue_size = 0;
    ctx->queue.queue_index = 0;
    scanf("%d", &ctx->a);
    scanf("%d", &ctx->b);
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
