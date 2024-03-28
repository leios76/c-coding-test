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
    char s[1000001];
    int buffer[1000001];
    int read_index;
    int write_index;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int state = 0;
    int r;
    int w;
    for (int m = 0; m < ctx->m; m++) {
        if (ctx->s[m] == 'I') {
            if (state == 1) {
                ctx->read_index = ctx->write_index;
            }
            state = 1;
            ctx->buffer[ctx->write_index++] = m;

            r = ctx->read_index;
            w = ctx->write_index;

            while (r != w) {
                if (m - ctx->buffer[r++] == ctx->n * 2) {
                    result++;
                    ctx->read_index++;
                } else {
                    break;
                }
            };
        } else {
            if (state == 0) {
                ctx->read_index = ctx->write_index;
            }
            state = 0;
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    scanf("%s", ctx->s);
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
