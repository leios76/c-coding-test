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
    struct queue_entity_t queue_pool[25 * 25];
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
    int v[25 * 25];

    int size[25 * 25];
    int size_count;

    struct queue_t queue;
};
struct context_t context;


int sort_buffer[25 * 25];
void merge_sort(int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (arr[index] <= arr[right_index]) {
                sort_buffer[left_index++] = arr[index++];
            }
            else {
                sort_buffer[left_index++] = arr[right_index++];
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(int) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(int) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(int) * (right - left + 1));
	}
}

int set_group(struct context_t * ctx, int index)
{
    int x = index % 25;
    int y = index / 25;
    int size = 0;

    ctx->queue.queue_pool[index].g = ctx->size_count;
    size++;

    if (x > 0) {
        if (ctx->queue.queue_pool[index - 1].g == -1 && ctx->queue.queue_pool[index - 1].s == 1) {
            size += set_group(ctx, index - 1);
        }
    }
    if (x < ctx->n - 1) {
        if (ctx->queue.queue_pool[index + 1].g == -1 && ctx->queue.queue_pool[index + 1].s == 1) {
            size += set_group(ctx, index + 1);
        }
    }
    if (y > 0) {
        if (ctx->queue.queue_pool[index - 25].g == -1 && ctx->queue.queue_pool[index - 25].s == 1) {
            size += set_group(ctx, index - 25);
        }
    }
    if (y < ctx->n - 1) {
        if (ctx->queue.queue_pool[index + 25].g == -1 && ctx->queue.queue_pool[index + 25].s == 1) {
            size += set_group(ctx, index + 25);
        }
    }
    return size;
}

void solve(struct context_t * ctx)
{
    while (ctx->queue.queue_size > 0) {
        int index = ctx->queue.queue_head_index;
        remove_queue(&ctx->queue, index);
        if (ctx->queue.queue_pool[index].g == -1 && ctx->queue.queue_pool[index].s == 1) {
            ctx->size[ctx->size_count++] = set_group(ctx, index);
        }
    }
    printf("%d\n", ctx->size_count);
    merge_sort(ctx->size, 0, ctx->size_count - 1);
    for (int s = 0; s < ctx->size_count; s++) {
        printf("%d\n", ctx->size[s]);
    }

}

void init_data(struct context_t * ctx)
{
    char line[26];
    memset(ctx, 0, sizeof(struct context_t));
    memset(&ctx->queue, -1, sizeof(ctx->queue));
    ctx->queue.queue_size = 0;
    scanf("%d", &ctx->n);

    for (int ny = 0; ny < ctx->n; ny++) {
        scanf("%s", line);
        for (int nx = 0; nx < ctx->n; nx++) {
            ctx->queue.queue_pool[ny * 25 + nx].s = line[nx] - '0';
            if (ctx->queue.queue_pool[ny * 25 + nx].s == 1) {
                insert_queue(&ctx->queue, ctx->queue.queue_tail_index, -1, ny * 25 + nx);
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
