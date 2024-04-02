#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
    int queue[10000];
    int queue_read;
    int queue_written;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    char command[8];
    int value;

    ctx->queue_read = 0;
    ctx->queue_written = 0;

    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", command);
        if (strcmp(command, "push") == 0) {
            scanf("%d", &value);
            ctx->queue[ctx->queue_written] = value;
            ctx->queue_written = (ctx->queue_written + 1) % 10000;
        }
        if (strcmp(command, "pop") == 0) {
            if (ctx->queue_read == ctx->queue_written) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue[ctx->queue_read]);
                ctx->queue_read = (ctx->queue_read + 1) % 10000;
            }
        }
        if (strcmp(command, "size") == 0) {
            printf("%d\n", ctx->queue_written - ctx->queue_read);
        }
        if (strcmp(command, "empty") == 0) {
            if (ctx->queue_read == ctx->queue_written) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
        if (strcmp(command, "front") == 0) {
            if (ctx->queue_read == ctx->queue_written) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue[ctx->queue_read]);
            }
        }
        if (strcmp(command, "back") == 0) {
            if (ctx->queue_read == ctx->queue_written) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->queue[ctx->queue_written - 1]);
            }
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
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
