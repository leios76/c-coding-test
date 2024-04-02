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
    int bitmask;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    char command[8];
    int value;

    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", command);
        if (strcmp(command, "add") == 0) {
            scanf("%d", &value);
            ctx->bitmask |= (1 << value);
        }
        if (strcmp(command, "remove") == 0) {
            scanf("%d", &value);
            ctx->bitmask &= ~(1 << value);
        }
        if (strcmp(command, "check") == 0) {
            scanf("%d", &value);
            printf("%d\n", (ctx->bitmask >> value) & 0x01);
        }
        if (strcmp(command, "toggle") == 0) {
            scanf("%d", &value);
            ctx->bitmask ^= (1 << value);
        }
        if (strcmp(command, "all") == 0) {
            ctx->bitmask = (1 << 21) - 1;
        }
        if (strcmp(command, "empty") == 0) {
            ctx->bitmask = 0;
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
