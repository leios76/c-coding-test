#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
    #define DEBUG_QUEUE
#else
    #define debug(...)
#endif


struct queue_entity_t {
    int n;
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
    #ifdef DEBUG_QUEUE
    debug("remove queue %d / %d %d\n", index);
    #endif
    queue->queue_size--;
    if (index == queue->queue_tail_index) {
        #ifdef DEBUG_QUEUE
        debug(" update tail index: %d -> %d\n", queue->queue_tail_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_tail_index = queue->queue_pool[index].prev_index;
    }
    if (index == queue->queue_head_index) {
        #ifdef DEBUG_QUEUE
        debug(" update head index: %d -> %d\n", queue->queue_head_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_head_index = queue->queue_pool[index].next_index;
    }

    if (queue->queue_pool[index].prev_index != -1) {
        #ifdef DEBUG_QUEUE
        debug(" update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, queue->queue_pool[index].next_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].prev_index].next_index = queue->queue_pool[index].next_index;
    }
    if (queue->queue_pool[index].next_index != -1) {
        #ifdef DEBUG_QUEUE
        debug(" update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, queue->queue_pool[index].prev_index);
        #endif
        queue->queue_pool[queue->queue_pool[index].next_index].prev_index = queue->queue_pool[index].prev_index;
    }
}

void insert_queue(struct queue_t * queue, int after, int before, int index)
{
    #ifdef DEBUG_QUEUE
    debug("insert queue %d / %d / %d\n", after, index, before);
    #endif
    queue->queue_size++;
    if (queue->queue_head_index == -1 && queue->queue_tail_index == -1) {
        #ifdef DEBUG_QUEUE
        debug(" update head index: %d -> %d\n", queue->queue_head_index, index);
        #endif
        queue->queue_head_index = index;
        #ifdef DEBUG_QUEUE
        debug(" update tail index: %d -> %d\n", queue->queue_tail_index, index);
        #endif
        queue->queue_tail_index = index;
        queue->queue_pool[index].prev_index = -1;
        queue->queue_pool[index].next_index = -1;
    } else {
        if (after != -1) {
            #ifdef DEBUG_QUEUE
            debug(" update next index (%d): %d -> %d\n", index, -1, queue->queue_pool[after].next_index);
            #endif
            queue->queue_pool[index].next_index = queue->queue_pool[after].next_index;
            #ifdef DEBUG_QUEUE
            debug(" update next index (%d): %d -> %d\n", after, queue->queue_pool[after].next_index, index);
            #endif
            queue->queue_pool[after].next_index = index;
            #ifdef DEBUG_QUEUE
            debug(" update prev index (%d): %d -> %d\n", index, queue->queue_pool[after].prev_index, after);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_tail_index;
            if (after == queue->queue_tail_index) {
                #ifdef DEBUG_QUEUE
                debug(" update tail index: %d -> %d\n", queue->queue_tail_index, index);
                #endif
                queue->queue_tail_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug(" update prev index (%d): %d -> %d\n", queue->queue_pool[index].next_index, queue->queue_pool[queue->queue_pool[index].next_index].prev_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].next_index].prev_index = index;
            }
        } else if (before != -1) {
            #ifdef DEBUG_QUEUE
            debug(" update prev index (%d): %d -> %d\n", index, -1, queue->queue_pool[before].prev_index);
            #endif
            queue->queue_pool[index].prev_index = queue->queue_pool[before].prev_index;
            #ifdef DEBUG_QUEUE
            debug(" update prev index (%d): %d -> %d\n", before, queue->queue_pool[before].prev_index, index);
            #endif
            queue->queue_pool[before].prev_index = index;
            #ifdef DEBUG_QUEUE
            debug(" update next index (%d): %d -> %d\n", index, queue->queue_pool[index].next_index, before);
            #endif
            queue->queue_pool[index].next_index = before;
            if (before == queue->queue_head_index) {
                #ifdef DEBUG_QUEUE
                debug(" update head index: %d -> %d\n", queue->queue_head_index, index);
                #endif
                queue->queue_head_index = index;
            } else {
                #ifdef DEBUG_QUEUE
                debug(" update next index (%d): %d -> %d\n", queue->queue_pool[index].prev_index, queue->queue_pool[queue->queue_pool[index].prev_index].next_index, index);
                #endif
                queue->queue_pool[queue->queue_pool[index].prev_index].next_index = index;
            }
        }
    }
}

struct context_t {
    int n;
    struct queue_t queue;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    char command[128];
    int value;

    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", command);
        debug("command: [%s]\n", command);
        if (strcmp(command, "push_front") == 0) {
            scanf("%d", &value);
            ctx->queue.queue_pool[n].n = value;
            insert_queue(&ctx->queue, -1, ctx->queue.queue_head_index, n);
        }
        if (strcmp(command, "push_back") == 0) {
            scanf("%d", &value);
            ctx->queue.queue_pool[n].n = value;
            insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, n);
        }
        if (strcmp(command, "pop_front") == 0) {
            if (ctx->queue.queue_size == 0) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue.queue_pool[ctx->queue.queue_head_index].n);
                remove_queue(&ctx->queue, ctx->queue.queue_head_index);
            }
        }
        if (strcmp(command, "pop_back") == 0) {
            if (ctx->queue.queue_size == 0) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue.queue_pool[ctx->queue.queue_tail_index].n);
                remove_queue(&ctx->queue, ctx->queue.queue_tail_index);
            }
        }
        if (strcmp(command, "size") == 0) {
            printf("%d\n", ctx->queue.queue_size);
        }
        if (strcmp(command, "empty") == 0) {
            if (ctx->queue.queue_size == 0) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
        if (strcmp(command, "front") == 0) {
            if (ctx->queue.queue_size == 0) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue.queue_pool[ctx->queue.queue_head_index].n);
            }
        }
        if (strcmp(command, "back") == 0) {
            if (ctx->queue.queue_size == 0) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue.queue_pool[ctx->queue.queue_tail_index].n);
            }
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    scanf("%d", &ctx->n);
    ctx->queue.queue_size = 0;
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
