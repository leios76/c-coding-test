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
    char line[1000001];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int state = 0;
    int length = strlen(ctx->line);
    for (int i = 0; i < length;) {
        debug("check [%c] state %d result %d\n", ctx->line[i], state, result);
        switch (state) {
        case 0:
            if (ctx->line[i] != ' ') {
                state = 1;
            } else {
                i++;
            }
            break;
        case 1:
            if (ctx->line[i] == ' ') {
                result++;
                state = 0;
            } else {
                i++;
            }
            if (i == length) {
                result++;
            }
            break;
        case 2:
            break;
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%[^\n]s", ctx->line);
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
