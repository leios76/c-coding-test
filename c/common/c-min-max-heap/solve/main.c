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
};

struct heap_t {
    struct heap_entity_t heap_pool[100001];
    int heap_size;
    int is_min;
};

void enqueue(struct heap_t * heap, int v)
{
    int i = ++heap->heap_size;
    if (heap->is_min) {
        while (i > 1 && v < heap->heap_pool[i / 2].v) {
            heap->heap_pool[i].v = heap->heap_pool[i / 2].v;
            i /= 2;
        }
    } else {
        while (i > 1 && v > heap->heap_pool[i / 2].v) {
            heap->heap_pool[i].v = heap->heap_pool[i / 2].v;
            i /= 2;
        }
    }
    heap->heap_pool[i].v = v;
}

void heapify(struct heap_t * heap, int i)
{
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (heap->is_min) {
        if (left <= heap->heap_size && heap->heap_pool[left].v < heap->heap_pool[i].v) {
            largest = left;
        }
        if (right <= heap->heap_size && heap->heap_pool[right].v < heap->heap_pool[largest].v) {
            largest = right;
        }
    } else {
        if (left <= heap->heap_size && heap->heap_pool[left].v > heap->heap_pool[i].v) {
            largest = left;
        }
        if (right <= heap->heap_size && heap->heap_pool[right].v > heap->heap_pool[largest].v) {
            largest = right;
        }
    }

    if (largest != i) {
        int temp = heap->heap_pool[i].v;
        heap->heap_pool[i].v = heap->heap_pool[largest].v;
        heap->heap_pool[largest].v = temp;
        heapify(heap, largest);
    }
}

int peek(struct heap_t * heap)
{
    return heap->heap_pool[1].v;
}

int dequeue(struct heap_t * heap)
{
    int max = heap->heap_pool[1].v;
    heap->heap_pool[1].v = heap->heap_pool[heap->heap_size].v;
    heap->heap_size--;
    heapify(heap, 1);

    return max;
}

struct context_t {
    int n;
    int v[100000];
    struct heap_t heap;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int index;
    for (int n = 0; n < ctx->n; n++) {
        if (ctx->v[n] == 0) {
            if (ctx->heap.heap_size == 0) {
                printf("%d\n", 0);
            } else {
                printf("%d\n", dequeue(&ctx->heap));
            }
        } else {
            enqueue(&ctx->heap, ctx->v[n]);
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->v[n]);
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
