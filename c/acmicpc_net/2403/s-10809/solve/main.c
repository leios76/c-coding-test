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
    char line[101];
    int start[26];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    for (int i = 0; i < strlen(ctx->line); i++) {
        if (ctx->start[ctx->line[i] - 'a'] == -1) {
            ctx->start[ctx->line[i] - 'a'] = i;
        }
    }
    for (int i = 0; i < 26; i++) {
        printf("%d ", ctx->start[i]);
    }
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->start, -1, sizeof(ctx->start));
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
