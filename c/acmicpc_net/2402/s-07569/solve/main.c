#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct dynamic_queue_t {
    int read_index;
    int written_index;
    int turn_index;
    int queue_size;

    int * data;
};
struct context_t {
    int h;
    int n;
    int m;

    int remain;
    int turn;

    struct dynamic_queue_t queue;

    int tbl[128 * 128 * 128];
};
struct context_t context;


int pop_queue(struct dynamic_queue_t * queue)
{
    int value;
    value = queue->data[queue->read_index];
    queue->read_index = (queue->read_index + 1) % queue->queue_size;
    return value;
}

void push_queue(struct dynamic_queue_t * queue, int value)
{
    if (queue->queue_size == 0) {
        queue->queue_size = 1024 * 128;
        queue->data = (int *)malloc(sizeof(int) * queue->queue_size);
    }

    if ((queue->written_index + 1) % queue->queue_size == queue->read_index) {
        int * temp = (int *)malloc(sizeof(int) * queue->queue_size * 2);
        memcpy(&temp[0], &queue->data[queue->read_index], sizeof(int) * (queue->queue_size - queue->read_index));
        if (queue->read_index > 0) {
            memcpy(&temp[queue->queue_size - queue->read_index], &queue->data[0], sizeof(int) * (queue->written_index + 1));
        }
        free(queue->data);

        queue->turn_index = (queue->turn_index + queue->queue_size - queue->read_index) % queue->queue_size;
        queue->read_index = 0;
        queue->written_index = queue->queue_size - 1;
        queue->queue_size = queue->queue_size * 2;
        queue->data = temp;
    }

    queue->data[queue->written_index] = value;
    queue->written_index = (queue->written_index + 1) % queue->queue_size;
}

void solve(struct context_t * ctx)
{
    int result = 0;

    int diff[6] = {-1, 1, -128, 128, -16384, 16384};
    int diff_h[6] = {0, 0, 0, 0, -1, 1};
    int diff_n[6] = {0, 0, -1, 1, 0, 0};
    int diff_m[6] = {-1, 1, 0, 0, 0, 0};
    struct dynamic_queue_t * queue = &ctx->queue;
    while (queue->read_index != queue->written_index) {
        queue->turn_index = queue->written_index;
        while (queue->read_index != queue->turn_index) {
            int coord = pop_queue(queue);

            int h = coord / 16384;
            int n = (coord / 128) % 128;
            int m = coord % 128;
            debug("pop queue: %d, %d, %d\n", h, n, m);
            for (int i = 0; i < 6; i++) {
                int nh = h + diff_h[i];
                int nm = m + diff_m[i];
                int nn = n + diff_n[i];
                if (nh < 0 || nm < 0 || nn < 0 || nh >= ctx->h || nm >= ctx->m || nn >= ctx->n) {
                    continue;
                }
                debug("check %d, %d, %d = %d\n", nh, nn, nm, ctx->tbl[coord + diff[i]]);
                switch (ctx->tbl[coord + diff[i]]) {
                    case 0:
                        ctx->tbl[coord + diff[i]] = ctx->turn + 1;
                        push_queue(queue, coord + diff[i]);
                        ctx->remain--;
                        debug("add queue: %d, %d, %d\n", nh, nn, nm);
                        break;
                }
            }
        }
        ctx->turn++;
    }
    if (ctx->remain == 0) {
        printf("%d\n", ctx->turn - 1);
    } else {
        printf("-1\n");
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d%d", &ctx->n, &ctx->m, &ctx->h);
    for (int h = 0; h < ctx->h; h++) {
        for (int m = 0; m < ctx->m; m++) {
            for (int n = 0; n < ctx->n; n++) {
                scanf("%d", &ctx->tbl[h * 16384 + n * 128 + m]);
                debug("set %d, %d => %d\n", n, m, ctx->tbl[h * 16384 + n * 128 + m]);
                if (ctx->tbl[h * 16384 + n * 128 + m] == 1) {
                    debug("add queue: %d, %d\n", n, m);
                    push_queue(&ctx->queue, h * 16384 + n * 128 + m);
                } else if (ctx->tbl[h * 16384 + n * 128 + m] == 0) {
                    ctx->remain++;
                }
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
