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

    for (int l = 0; l < strlen(ctx->line); l++) {
        if (ctx->line[l] == '(') {
            result++;
        } else if (ctx->line[l] == ')') {
            result--;
        }
        if (result < 0) {
            break;
        }
    }

    printf("%s\n", (result == 0) ? "YES" : "NO");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%s", ctx->line);
}

int main(int argc, char ** argv)
{
    int t = 1;

    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
