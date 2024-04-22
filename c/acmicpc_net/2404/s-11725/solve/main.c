#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct entry_t {
    int parent;

    int buffer_head;
    int buffer_tail;
};

struct buffer_queue_entity_t {
    int index[15];
    int count;
    int prev_index;
    int next_index;
};

struct buffer_queue_t {
    struct buffer_queue_entity_t queue_pool[100000];
    int queue_size;
};

struct queue_entity_t {
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[100000];
    int queue_head_index;
    int queue_tail_index;
    int queue_size;
};

struct context_t {
    int n;
    struct entry_t entries[100000];

    struct buffer_queue_t buffer_queue;
    struct queue_t entry_queue;
};
struct context_t context;


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

void solve(struct context_t * ctx)
{
    int buffer_index;
    int entry_index;
    int child_entry_index;

    insert_queue(&ctx->entry_queue, -1, -1, 0);
    ctx->entries[0].parent = 0;
    entry_index = ctx->entry_queue.queue_head_index;

    while (entry_index != -1) {
        remove_queue(&ctx->entry_queue, entry_index);

        buffer_index = ctx->entries[entry_index].buffer_head;
        while (buffer_index != -1) {
            for (int count = 0; count < ctx->buffer_queue.queue_pool[buffer_index].count; count++) {
                child_entry_index = ctx->buffer_queue.queue_pool[buffer_index].index[count];

                if (ctx->entries[child_entry_index].parent == -1) {
                    insert_queue(&ctx->entry_queue, ctx->entry_queue.queue_tail_index, -1, child_entry_index);
                    ctx->entries[child_entry_index].parent = entry_index;
                }
            }

            buffer_index = ctx->buffer_queue.queue_pool[buffer_index].next_index;
        }

        entry_index = ctx->entry_queue.queue_head_index;
    }
    for (int n = 1; n < ctx->n; n++) {
        printf("%d\n", ctx->entries[n].parent + 1);
    }
}

void init_data(struct context_t * ctx)
{
    int p;
    int c;
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->entries, -1, sizeof(ctx->entries));

    ctx->entry_queue.queue_head_index = -1;
    ctx->entry_queue.queue_tail_index = -1;

    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n - 1; n++) {
        scanf("%d%d", &p, &c);
        p--;
        c--;

        if (ctx->entries[p].buffer_head == -1) {
            ctx->entries[p].buffer_head = ctx->buffer_queue.queue_size;
            ctx->entries[p].buffer_tail = ctx->buffer_queue.queue_size;
            ctx->buffer_queue.queue_pool[ctx->buffer_queue.queue_size].next_index = -1;
            ctx->buffer_queue.queue_size++;
        } else if (ctx->buffer_queue.queue_pool[ctx->entries[p].buffer_tail].count == 15) {
            ctx->buffer_queue.queue_pool[ctx->entries[p].buffer_tail].next_index = ctx->buffer_queue.queue_size;
            ctx->entries[p].buffer_tail = ctx->buffer_queue.queue_size;
            ctx->buffer_queue.queue_pool[ctx->buffer_queue.queue_size].next_index = -1;
            ctx->buffer_queue.queue_size++;
        }
        ctx->buffer_queue.queue_pool[ctx->entries[p].buffer_tail].index[ctx->buffer_queue.queue_pool[ctx->entries[p].buffer_tail].count++] = c;

        if (ctx->entries[c].buffer_head == -1) {
            ctx->entries[c].buffer_head = ctx->buffer_queue.queue_size;
            ctx->entries[c].buffer_tail = ctx->buffer_queue.queue_size;
            ctx->buffer_queue.queue_pool[ctx->buffer_queue.queue_size].next_index = -1;
            ctx->buffer_queue.queue_size++;
        } else if (ctx->buffer_queue.queue_pool[ctx->entries[c].buffer_tail].count == 15) {
            ctx->buffer_queue.queue_pool[ctx->entries[c].buffer_tail].next_index = ctx->buffer_queue.queue_size;
            ctx->entries[c].buffer_tail = ctx->buffer_queue.queue_size;
            ctx->buffer_queue.queue_pool[ctx->buffer_queue.queue_size].next_index = -1;
            ctx->buffer_queue.queue_size++;
        }
        ctx->buffer_queue.queue_pool[ctx->entries[c].buffer_tail].index[ctx->buffer_queue.queue_pool[ctx->entries[c].buffer_tail].count++] = p;
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
