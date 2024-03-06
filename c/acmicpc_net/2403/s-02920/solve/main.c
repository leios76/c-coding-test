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
    int n[8];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int direction = -1;
    char result[3][32] = {"ascending", "descending", "mixed"};
    for (int n = 1; n < 8; n++) {
        if (ctx->n[n] > ctx->n[n - 1]) {
            if (direction == -1) {
                direction = 0;
            } else if (direction == 1) {
                direction = 2;
            }
        } else if (ctx->n[n] < ctx->n[n - 1]) {
            if (direction == -1) {
                direction = 1;
            } else if (direction == 0) {
                direction = 2;
            }
        }
    }


    printf("%s\n", result[direction]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    for (int n = 0; n < 8; n++)  {
        scanf("%d", &ctx->n[n]);
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
