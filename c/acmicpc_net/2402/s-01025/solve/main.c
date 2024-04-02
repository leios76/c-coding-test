#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
    int m;
    int tbl[9][9];
};
struct context_t context;

int check_number(int a)
{
    int r = sqrt(a);
    return (r * r) == a;
}

int make_number(struct context_t * ctx, int start_r, int start_c, int move_r, int move_c)
{
    int max_v = -1;
    int v = 0;
    int n = start_r;
    int m = start_c;
    for (; n >= 0 && n < ctx->n && m >= 0 && m < ctx->m;) {
        v = v * 10 + ctx->tbl[n][m];
        if (check_number(v) && max_v < v) {
            max_v = v;
        }
        if (move_c == 0 && move_r == 0) {
            break;
        }
        n += move_r;
        m += move_c;
    }
    return max_v;
}

void solve(struct context_t * ctx)
{
    int result = -1;

    for (int n = 1 - ctx->n; n < ctx->n; n++) {
        for (int m = 1 - ctx->m; m < ctx->m; m++) {
            for (int r = 0; r < ctx->n; r++) {
                for (int c = 0; c < ctx->m; c++) {
                    int v = make_number(ctx, r, c, n, m);
                    if (result < v) {
                        //debug("%d %d %d %d ==> %d\n", r, c, n, m, v);
                        result = v;
                    }
                }
            }
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    char line[10];
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", line);

        for (int m = 0; m < ctx->m; m++) {
            ctx->tbl[n][m] = line[m] - '0';
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
