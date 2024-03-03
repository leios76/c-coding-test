#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct queue_t {
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

    struct queue_t queue;
    int area[1024 * 1024];
};
struct context_t context;

int target_r = -2;
int target_c = -2;

void print_board(struct context_t * ctx, int range)
{
    if (target_r == -2 && target_c == -2) {
        target_r = -1;
        target_c = -1;
        for (int r = 0; r < ctx->r; r++) {
            for (int c = 0; c < ctx->c; c++) {
                switch (ctx->area[r * 1024 + c]) {
                case 0xFFFFFFF:
                    target_r = r;
                    target_c = c;
                    r = ctx->r;
                    c = ctx->c;
                    break;
                }
            }
        }
    }
    if (target_r == -1 && target_c == -1) {
        return;
    }
    for (int r = -range; r < range; r++) {
        if (r + target_r < 0 || r + target_r > ctx->r - 1) {
            continue;
        }
        for (int c = -range; c < range; c++) {
            if (c + target_c < 0 || c + target_c > ctx->c - 1) {
                continue;
            }
            switch (ctx->area[(target_r + r) * 1024 + (target_c + c)]) {
            case 0xFFFFFFF:
                printf("&");
                break;
            case -1:
                printf(".");
                break;
            case -1000:
                printf("#");
                break;
            default:
                printf("%d", ctx->area[(target_r + r) * 1024 + (target_c + c)]);
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

int pop_queue(struct queue_t * queue)
{
    int value;
    value = queue->data[queue->read_index];
    queue->read_index = (queue->read_index + 1) % queue->queue_size;
    return value;
}

void push_queue(struct queue_t * queue, int value)
{
    if (queue->queue_size == 0) {
        queue->queue_size = 1024 * 4;
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
#ifdef DEBUG_OUTPUT
        printf("increase queue size: %d -> %d\n", queue->queue_size, queue->queue_size * 2);
#endif
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
    struct queue_t * queue = &ctx->queue;
    while (queue->read_index != queue->written_index) {
        queue->turn_index = queue->written_index;
#ifdef DEBUG_OUTPUT
        printf("process %d turn...(r%d w%d)\n", ctx->turn, ctx->queue.read_index, ctx->queue.written_index);
#endif
        while (queue->read_index != queue->turn_index) {
            int coord = pop_queue(queue);

            int c = coord % 1024;
            int r = coord / 1024;
#ifdef DEBUG_OUTPUT
            if (target_r > -1 && target_c > -1 && target_r - 12 < r && r < target_r + 12 && target_c - 12 < c && c < target_c + 12) {
                //printf("process %d,%d (%d) (r%d w%d)\n", c, r, ctx->area[coord], ctx->queue.read_index, ctx->queue.written_index);
            }
#endif
            for (int i = 0; i < 4; i++) {
                int nc = c + diff_c[i];
                int nr = r + diff_r[i];
                if (nc < 0 || nr < 0 || nc >= ctx->c || nr >= ctx->r) {
                    continue;
                }
#ifdef DEBUG_OUTPUT
                //printf(" %d dir(%d) %d\n", coord + diff[i], diff[i], ctx->area[coord + diff[i]]);
#endif
                switch (ctx->area[coord + diff[i]]) {
                case 0xFFFFFFF:
                    return ctx->turn;

                case -1:
#ifdef DEBUG_OUTPUT
                    //printf(" ==> add %d,%d (%d) (r%d w%d)\n", nc, nr, ctx->turn + 1, ctx->queue.read_index, ctx->queue.written_index);
#endif
                    ctx->area[coord + diff[i]] = ctx->turn + 1;
                    push_queue(queue, coord + diff[i]);
                    break;
                }
            }
        }
        ctx->turn++;
#ifdef DEBUG_OUTPUT
        //print_board(ctx, 15);
#endif
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
                ctx->area[coord] = -1000;
                break;
            case '&':
                ctx->area[coord] = 0xFFFFFFF;
                break;
            case '@':
                ctx->area[coord] = 0;
                push_queue(&ctx->queue, coord);
                break;
            }
        }
    }
}

int main()
{
    init_data(&context);
    int output = solve(&context);
    printf("%d\n", output);

    if (context.queue.data) {
        free(context.queue.data);
    }

    return 0;
}
