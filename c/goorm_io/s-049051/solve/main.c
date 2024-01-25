#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct dynamic_queue_t {
    int read_index;
    int written_index;
    int turn_index;
    int queue_size;

    int * data;
};

struct context_t {
    int r;
    int c;

    int turn;

    struct dynamic_queue_t queue;
    int area[1024 * 1024];
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

int solve(struct context_t * ctx)
{
    int diff[4] = { -1, 1, -1024, 1024 };
    int diff_c[4] = { -1, 1, 0, 0 };
    int diff_r[4] = { 0, 0, -1, 1 };
    struct dynamic_queue_t * queue = &ctx->queue;
    while (queue->read_index != queue->written_index) {
        queue->turn_index = queue->written_index;
        while (queue->read_index != queue->turn_index) {
            int coord = pop_queue(queue);

            int c = coord % 1024;
            int r = coord / 1024;
            for (int i = 0; i < 4; i++) {
                int nc = c + diff_c[i];
                int nr = r + diff_r[i];
                if (nc < 0 || nr < 0 || nc >= ctx->c || nr >= ctx->r) {
                    continue;
                }
                switch (ctx->area[coord + diff[i]]) {
                case -3:
                    return ctx->turn;

                case -1:
                    ctx->area[coord + diff[i]] = ctx->turn + 1;
                    push_queue(queue, coord + diff[i]);
                    break;
                }
            }
        }
        ctx->turn++;
    }
    return -1;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    char line[1024];

    scanf("%d %d", &ctx->r, &ctx->c);
    for (int r = 0; r < ctx->r; r++) {
        scanf("%s", line);
        for (int c = 0; c < ctx->c; c++) {
            int coord = r * 1024 + c;
            switch (line[c]) {
            case '.':
                ctx->area[coord] = -1;
                break;
            case '#':
                ctx->area[coord] = -2;
                break;
            case '&':
                ctx->area[coord] = -3;
                break;
            case '@':
                push_queue(&ctx->queue, coord);
                break;
            }
        }
    }
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    if (context.queue.data) {
        free(context.queue.data);
    }

    return 0;
}
