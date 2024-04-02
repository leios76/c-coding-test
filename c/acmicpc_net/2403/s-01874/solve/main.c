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
    int current_number;
    int numbers[100000];
    int stack[100000];
    int stack_pos;
    int stack_op_count;
    char stack_op[1000000];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    ctx->stack_pos = -1;
    for (int n = 0; n < ctx->n; n++) {
        if (ctx->stack_pos == -1) {
            ctx->stack[++ctx->stack_pos] = ++ctx->current_number;
            ctx->stack_op[ctx->stack_op_count++] = '+';
        }
        while (ctx->stack_pos < 100000 && ctx->stack[ctx->stack_pos] != ctx->numbers[n]) {
            ctx->stack[++ctx->stack_pos] = ++ctx->current_number;
            ctx->stack_op[ctx->stack_op_count++] = '+';
        }
        if (ctx->stack_pos > -1 && ctx->stack_pos < 100000 && ctx->stack[ctx->stack_pos] == ctx->numbers[n]) {
            ctx->stack_op[ctx->stack_op_count++] = '-';
            ctx->stack_pos--;
        }
    }
    if (ctx->stack_pos == -1) {
        for (int c = 0; c < ctx->stack_op_count; c++) {
            printf("%c\n", ctx->stack_op[c]);
        }
    } else {
        printf("NO\n");
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->numbers[n]);
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
