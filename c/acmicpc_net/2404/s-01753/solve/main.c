#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct road_t {
    int s;
    int e;
    int w;

    int n;
};


struct heap_entity_t {
    int v;
    int w;
};

struct heap_t {
    struct heap_entity_t heap_pool[300000];
    int heap_size;
    int is_min;
};

void enqueue(struct heap_t * heap, int v, int w)
{
    if (heap->heap_size >= 300000) {
        return;
    }
    int i = ++heap->heap_size;
    if (heap->is_min) {
        while (i > 1 && w < heap->heap_pool[i / 2].w) {
            heap->heap_pool[i].v = heap->heap_pool[i / 2].v;
            heap->heap_pool[i].w = heap->heap_pool[i / 2].w;
            i /= 2;
        }
    } else {
        while (i > 1 && w > heap->heap_pool[i / 2].w) {
            heap->heap_pool[i].v = heap->heap_pool[i / 2].v;
            heap->heap_pool[i].w = heap->heap_pool[i / 2].w;
            i /= 2;
        }
    }
    heap->heap_pool[i].v = v;
    heap->heap_pool[i].w = w;
}

void heapify(struct heap_t * heap, int i)
{
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (heap->is_min) {
        if (left <= heap->heap_size && heap->heap_pool[left].w < heap->heap_pool[i].w) {
            largest = left;
        }
        if (right <= heap->heap_size && heap->heap_pool[right].w < heap->heap_pool[largest].w) {
            largest = right;
        }
    } else {
        if (left <= heap->heap_size && heap->heap_pool[left].w > heap->heap_pool[i].w) {
            largest = left;
        }
        if (right <= heap->heap_size && heap->heap_pool[right].w > heap->heap_pool[largest].w) {
            largest = right;
        }
    }

    if (largest != i) {
        int temp_v = heap->heap_pool[i].v;
        int temp_w = heap->heap_pool[i].w;
        heap->heap_pool[i].v = heap->heap_pool[largest].v;
        heap->heap_pool[i].w = heap->heap_pool[largest].w;
        heap->heap_pool[largest].v = temp_v;
        heap->heap_pool[largest].w = temp_w;
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
    heap->heap_pool[1].w = heap->heap_pool[heap->heap_size].w;
    heap->heap_size--;
    heapify(heap, 1);

    return max;
}

struct context_t {
    int v;
    int e;
    int k;
    struct road_t roads[300000];
    int node_head[20001];
    int node_tail[20001];
    int dist[20001];
    struct heap_t heap;
};

struct context_t context;

void solve(struct context_t * ctx)
{
    int index = 0;
    ctx->heap.is_min = 1;

    ctx->dist[ctx->k] = 0;

    enqueue(&ctx->heap, ctx->k, 0);

    while (ctx->heap.heap_size > 0) {
        int x = ctx->heap.heap_pool[1].w;
        int U = ctx->heap.heap_pool[1].v;

        index = dequeue(&ctx->heap);

        int e = ctx->node_head[index];

        while (e != -1) {
            int V = ctx->roads[e].e;
            int W = ctx->roads[e].w;

            if (x+W < ctx->dist[V]) {
                ctx->dist[V] = x+W;
                enqueue(&ctx->heap, V, x+W);
            }
            e = ctx->roads[e].n;
        }
    }
    for (int v = 1; v <= ctx->v; v++) {
        if (ctx->dist[v] == 0x77777777) {
            printf("INF\n");
        } else {
            printf("%d\n", ctx->dist[v]);
        }
    }
}

void init_data(struct context_t * ctx)
{
    int u;
    int v;
    int w;
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dist, 0x77, sizeof(ctx->dist));
    memset(ctx->node_head, -1, sizeof(ctx->node_head));
    memset(ctx->node_tail, -1, sizeof(ctx->node_tail));

    scanf("%d", &ctx->v);
    scanf("%d", &ctx->e);
    scanf("%d", &ctx->k);
    for (int e = 0; e < ctx->e; e++) {
        scanf("%d%d%d", &ctx->roads[e].s, &ctx->roads[e].e, &ctx->roads[e].w);
        ctx->roads[e].n = -1;
        if (ctx->node_head[ctx->roads[e].s] == -1) {
            ctx->node_head[ctx->roads[e].s] = e;
            ctx->node_tail[ctx->roads[e].s] = e;
        } else {
            ctx->roads[ctx->node_tail[ctx->roads[e].s]].n = e;
            ctx->node_tail[ctx->roads[e].s] = e;
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
