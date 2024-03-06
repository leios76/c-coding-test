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
    int stack[10000];
    int stack_pos;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    char command[8];
    int value;

    ctx->stack_pos = -1;
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", command);
        if (strcmp(command, "push") == 0) {
            scanf("%d", &value);
            ctx->stack[++ctx->stack_pos] = value;
        }
        if (strcmp(command, "pop") == 0) {
            if (ctx->stack_pos == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->stack[ctx->stack_pos]);
                ctx->stack_pos--;
            }
        }
        if (strcmp(command, "size") == 0) {
            printf("%d\n", ctx->stack_pos + 1);
        }
        if (strcmp(command, "empty") == 0) {
            if (ctx->stack_pos == -1) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
        if (strcmp(command, "top") == 0) {
            if (ctx->stack_pos == -1) {
                printf("-1\n");
            } else {
                printf("%d\n", ctx->stack[ctx->stack_pos]);
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
