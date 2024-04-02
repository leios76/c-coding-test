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
    int m;
    uint8_t table[100][100];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int n1 = 0; n1 < ctx->n; n1++) {
        for (int n2 = 0; n2 < ctx->n; n2++) {
            for (int n3 = 0; n3 < ctx->n; n3++) {
                if (ctx->table[n2][n3] > ctx->table[n2][n1] + ctx->table[n1][n3]) {
                    ctx->table[n2][n3] = ctx->table[n2][n1] + ctx->table[n1][n3];
                }
            }
        }
    }

    int min_index = 0;
    int min_sum = 0x7FFFFFFF;
    for (int n1 = 0; n1 < ctx->n; n1++) {
        int sum = 0;
        for (int n2 = 0; n2 < ctx->n; n2++) {
            debug("%d ", ctx->table[n1][n2]);
            sum += ctx->table[n1][n2];
        }
        if (min_sum > sum) {
            min_sum = sum;
            min_index = n1;
        }
        debug("\n");
    }


    printf("%d\n", min_index + 1);
}

void init_data(struct context_t * ctx)
{
    int s;
    int e;
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->table, -1, sizeof(ctx->table));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        ctx->table[n][n] = 0;
    }
    for (int m = 0; m < ctx->m; m++) {
        scanf("%d%d", &s, &e);
        ctx->table[s - 1][e - 1] = 1;
        ctx->table[e - 1][s - 1] = 1;
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
