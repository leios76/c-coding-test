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
    int r;
    char s[21];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    for (int c = 0; c < strlen(ctx->s); c++) {
        for (int r = 0; r < ctx->r; r++) {
            printf("%c", ctx->s[c]);
        }
    }
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->r);
    scanf("%s", ctx->s);
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
