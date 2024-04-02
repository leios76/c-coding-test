#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct heap_entity_t {
    int v;
    int d;
};

struct heap_t {
    struct heap_entity_t * heap_pool[1000000];
    int heap_size;
    int is_min;
};

struct context_t {
    int k;
    struct heap_entity_t pool[1000000];
    int pool_size;

    struct heap_t min_heap;
    struct heap_t max_heap;
};
struct context_t context;

void enqueue(struct heap_t * heap, struct heap_entity_t * entry)
{
    int i = ++heap->heap_size;
    if (heap->is_min) {
        while (i > 1 && entry->v < heap->heap_pool[i / 2]->v) {
            heap->heap_pool[i] = heap->heap_pool[i / 2];
            i /= 2;
        }
    } else {
        while (i > 1 && entry->v > heap->heap_pool[i / 2]->v) {
            heap->heap_pool[i] = heap->heap_pool[i / 2];
            i /= 2;
        }
    }
    heap->heap_pool[i] = entry;
}


void heapify(struct heap_t * heap, int i)
{
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (heap->is_min) {
        if (left <= heap->heap_size && heap->heap_pool[left]->v < heap->heap_pool[i]->v) {
            largest = left;
        }
        if (right <= heap->heap_size && heap->heap_pool[right]->v < heap->heap_pool[largest]->v) {
            largest = right;
        }
    } else {
        if (left <= heap->heap_size && heap->heap_pool[left]->v > heap->heap_pool[i]->v) {
            largest = left;
        }
        if (right <= heap->heap_size && heap->heap_pool[right]->v > heap->heap_pool[largest]->v) {
            largest = right;
        }
    }

    if (largest != i) {
        struct heap_entity_t * temp = heap->heap_pool[i];
        heap->heap_pool[i] = heap->heap_pool[largest];
        heap->heap_pool[largest] = temp;
        heapify(heap, largest);
    }
}


int dequeue(struct heap_t * heap)
{
    while (heap->heap_size > 0) {
        if (heap->heap_pool[1]->d == 1) {
            heap->heap_pool[1] = heap->heap_pool[heap->heap_size];
            heap->heap_size--;
            heapify(heap, 1);
        } else {
            int v = heap->heap_pool[1]->v;
            heap->heap_pool[1]->d = 1;
            heap->heap_pool[1] = heap->heap_pool[heap->heap_size];
            heap->heap_size--;
            heapify(heap, 1);
            return v;
        }
    }
    return 0;
}

void solve(struct context_t * ctx)
{
    char line[8];
    int v;
    ctx->min_heap.is_min = 1;
    for (int k = 0; k < ctx->k; k++) {
        scanf("%s", line);
        scanf("%d", &v);
        if (line[0] == 'I') {
            struct heap_entity_t * entry = &ctx->pool[ctx->pool_size++];
            entry->v = v;

            enqueue(&ctx->min_heap, entry);
            enqueue(&ctx->max_heap, entry);
        } else if (line[0] == 'D') {
            if (v == 1) {
                v = dequeue(&ctx->max_heap);
            } else if (v == -1) {
                v = dequeue(&ctx->min_heap);
            }
        }
    }

    while (ctx->max_heap.heap_size > 0 && ctx->max_heap.heap_pool[1]->d == 1) {
        ctx->max_heap.heap_pool[1] = ctx->max_heap.heap_pool[ctx->max_heap.heap_size];
        ctx->max_heap.heap_size--;
        heapify(&ctx->max_heap, 1);
    }

    while (ctx->min_heap.heap_size > 0 && ctx->min_heap.heap_pool[1]->d == 1) {
        ctx->min_heap.heap_pool[1] = ctx->min_heap.heap_pool[ctx->min_heap.heap_size];
        ctx->min_heap.heap_size--;
        heapify(&ctx->min_heap, 1);
    }

    if (ctx->max_heap.heap_size == 0 || ctx->min_heap.heap_size == 0) {
        printf("EMPTY\n");
    } else {
        printf("%d %d\n", ctx->max_heap.heap_pool[1]->v, ctx->min_heap.heap_pool[1]->v);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->k);
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
