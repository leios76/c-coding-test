#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct queue_t {
    int n;
    int h;
    int prev_index;
    int next_index;
};

struct context_t {
    int n;
    uint32_t result[500000];
    struct queue_t queue_pool[500000];
    int queue_head_index;
    int queue_tail_index;
};
struct context_t context;

void remove_queue(struct context_t * ctx, int index)
{
    if (index == ctx->queue_tail_index) {
        debug("update tail index: %d -> %d\n", ctx->queue_tail_index, ctx->queue_pool[index].prev_index);
        ctx->queue_tail_index = ctx->queue_pool[index].prev_index;
    }
    if (index == ctx->queue_head_index) {
        debug("update head index: %d -> %d\n", ctx->queue_head_index, ctx->queue_pool[index].next_index);
        ctx->queue_head_index = ctx->queue_pool[index].next_index;
    }

    if (ctx->queue_pool[index].prev_index != -1) {
        debug("update next index (%d): %d -> %d\n", ctx->queue_pool[index].prev_index, ctx->queue_pool[ctx->queue_pool[index].prev_index].next_index, ctx->queue_pool[index].next_index);
        ctx->queue_pool[ctx->queue_pool[index].prev_index].next_index = ctx->queue_pool[index].next_index;
    }
    if (ctx->queue_pool[index].next_index != -1) {
        debug("update prev index (%d): %d -> %d\n", ctx->queue_pool[index].next_index, ctx->queue_pool[ctx->queue_pool[index].next_index].prev_index, ctx->queue_pool[index].prev_index);
        ctx->queue_pool[ctx->queue_pool[index].next_index].prev_index = ctx->queue_pool[index].prev_index;
    }
}

void insert_queue(struct context_t * ctx, int after, int before, int index)
{

}


void solve(struct context_t * ctx)
{
    for (int n = 1; n < ctx->n; n++) {
        debug("process %d(%d)\n", n, ctx->queue_pool[n].h);
        int index = ctx->queue_tail_index;
        while (index != -1) {
            int prev_index = ctx->queue_pool[index].prev_index;
            if (ctx->queue_pool[index].h < ctx->queue_pool[n].h) {
                debug("remove %d(%d)\n", index, ctx->queue_pool[index].h);

                if (ctx->queue_head_index == -1 && ctx->queue_tail_index == -1) {
                    debug("add %d(%d)\n", n, ctx->queue_pool[n].h);
                    debug("update head index: %d -> %d\n", ctx->queue_head_index, n);
                    ctx->queue_head_index = n;
                    debug("update tail index: %d -> %d\n", ctx->queue_tail_index, n);
                    ctx->queue_tail_index = n;
                    ctx->queue_pool[n].prev_index = -1;
                    ctx->queue_pool[n].next_index = -1;
                }
            } else {
                ctx->result[n] = index + 1;
                debug("add %d(%d)\n", n, ctx->queue_pool[n].h);
                if (ctx->queue_head_index == -1 && ctx->queue_tail_index == -1) {
                    debug("update head index: %d -> %d\n", ctx->queue_head_index, n);
                    ctx->queue_head_index = n;
                    debug("update tail index: %d -> %d\n", ctx->queue_tail_index, n);
                    ctx->queue_tail_index = n;
                    ctx->queue_pool[n].prev_index = -1;
                    ctx->queue_pool[n].next_index = -1;
                } else {
                    debug("update next index (%d): %d -> %d\n", ctx->queue_tail_index, ctx->queue_pool[ctx->queue_tail_index].next_index, n);
                    ctx->queue_pool[ctx->queue_tail_index].next_index = n;
                    debug("update prev index (%d): %d -> %d\n", n, ctx->queue_pool[n].prev_index, ctx->queue_tail_index);
                    ctx->queue_pool[n].prev_index = ctx->queue_tail_index;
                    debug("update tail index: %d -> %d\n", ctx->queue_tail_index, n);
                    ctx->queue_tail_index = n;
                }
                break;
            }
            debug("next index: %d\n", prev_index);
            index = prev_index;
        }
    }

    for (int n = 0; n < ctx->n; n++) {
        printf("%d ", ctx->result[n]);
    }
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->queue_pool, 0xFF, sizeof(ctx->queue_pool));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        ctx->queue_pool[n].n = n;
        scanf("%d", &ctx->queue_pool[n].h);
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
