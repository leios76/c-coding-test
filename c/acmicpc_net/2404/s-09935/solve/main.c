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
    char line[1000001];
    char result[1000001];
    char keyword[37];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int d = 0;
    ctx->n = strlen(ctx->line);
    ctx->m = strlen(ctx->keyword);
    for (int n = 0; n < ctx->n; n++) {
        ctx->result[result++] = ctx->line[n];
        if (result >= ctx->m) {
            do {
                for (int m = 0; m < ctx->m; m++) {
                    if (ctx->result[result - ctx->m + m] != ctx->keyword[m]) {
                        d = 0;
                        break;
                    }
                    d++;
                }
                result -= d;
            } while (d != 0);
        }
    }
    ctx->result[result] = 0;

    if (strlen(ctx->result) == 0) {
        printf("FRULA\n");
    } else {
        printf("%s\n", ctx->result);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%s", ctx->line);
    scanf("%s", ctx->keyword);
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
