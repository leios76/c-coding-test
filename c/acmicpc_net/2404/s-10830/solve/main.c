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
    int64_t b;
    int arr[64][5][5];
    int result[5][5];
    int temp[5][5];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int i = 1; i < 64; i++) {
        for (int nr = 0; nr < ctx->n; nr++) {
            for (int nc = 0; nc < ctx->n; nc++) {
                for (int j = 0; j < ctx->n; j++) {
                    ctx->arr[i][nr][nc] += (ctx->arr[i - 1][nr][j] * ctx->arr[i - 1][j][nc]) % 1000;
                }
            }
        }
    }

    memcpy(ctx->result, ctx->arr[0], sizeof(int) * 5 * 5);
    ctx->b--;
    while (ctx->b > 0) {
        for (int i = 62; i >= 0; i--) {
            if (ctx->b >= (1L << i)) {
                memcpy(ctx->temp, ctx->result, sizeof(int) * 5 * 5);
                for (int nr = 0; nr < ctx->n; nr++) {
                    for (int nc = 0; nc < ctx->n; nc++) {
                        ctx->result[nr][nc] = 0;
                        for (int j = 0; j < ctx->n; j++) {
                            ctx->result[nr][nc] += (ctx->temp[nr][j] * ctx->arr[i][j][nc]) % 1000;
                        }
                    }
                }

                ctx->b -= (1L << i);
            }
        }
    }
    for (int nr = 0; nr < ctx->n; nr++) {
        for (int nc = 0; nc < ctx->n; nc++) {
            printf("%d ", ctx->result[nr][nc] % 1000);
        }
        printf("\n");
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%ld", &ctx->b);
    for (int nr = 0; nr < ctx->n; nr++) {
        for (int nc = 0; nc < ctx->n; nc++) {
            scanf("%d", &ctx->arr[0][nr][nc]);
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
