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
    char line[51];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int r = 1;
    int v = 0;
    for (int l = 0; l <= strlen(ctx->line); l++) {
        if ('0' <= ctx->line[l] && ctx->line[l] <= '9') {
            v = v * 10 + ctx->line[l] - '0';
        } else if (ctx->line[l] == '-') {
            result += v * r;
            r = -1;
            v = 0;
        } else {
            result += v * r;
            v = 0;
        }
    }

    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%s", ctx->line);
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
