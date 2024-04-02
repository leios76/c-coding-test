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
    int available;
    int count;
    int prev_index;
    int next_index;
};

struct queue_t {
    struct queue_entity_t queue_pool[1000001];
    int queue_head_index[1];
    int queue_tail_index[1];
    int queue_size[1];
};

void remove_queue(struct queue_t * queue, int queue_index, int index)
{
    if (queue->queue_pool[index].available == 0) {
        return;
    }
    queue->queue_size[queue_index]--;
    queue->queue_pool[index].available = 0;
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

int insert_queue(struct queue_t * queue, int queue_index, int after, int before, int index)
{
    if (queue->queue_pool[index].available == 1) {
        return 0;
    }
    queue->queue_size[queue_index]++;
    queue->queue_pool[index].available = 1;
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
    return 1;
}

struct queue_t queue;

int get_min_count(int n)
{
    int index;

    while (queue.queue_size[0] > 0) {
        index = queue.queue_head_index[0];
        if (index == 1) {
            return queue.queue_pool[index].count;
        }
        remove_queue(&queue, 0, index);

        if ((index % 3) == 0) {
            if (insert_queue(&queue, 0, queue.queue_tail_index[0], -1, index / 3)) {
                queue.queue_pool[index / 3].count = queue.queue_pool[index].count + 1;
            }
        }
        if ((index % 2) == 0) {
            if (insert_queue(&queue, 0, queue.queue_tail_index[0], -1, index / 2)) {
                queue.queue_pool[index / 2].count = queue.queue_pool[index].count + 1;
            }
        }
        if (insert_queue(&queue, 0, queue.queue_tail_index[0], -1, index - 1)) {
            queue.queue_pool[index - 1].count = queue.queue_pool[index].count + 1;
        }
    }

    return 0;
}

int main(int argc, char ** argv)
{
    int n;
    memset(&queue, -1, sizeof(queue));
    queue.queue_size[0] = 0;

    scanf("%d", &n);

    queue.queue_pool[n].count = 0;
    insert_queue(&queue, 0, queue.queue_head_index[0], -1, n);

    printf("%d\n", get_min_count(n));

    return 0;
}
