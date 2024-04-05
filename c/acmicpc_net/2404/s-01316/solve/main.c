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
    char word[101];
    int mask;
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    char old;
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", ctx->word);
        old = 0;
        ctx->mask = 0;
        result++;
        for (int i = 0; i < strlen(ctx->word); i++) {
            if (ctx->word[i] != old) {
                if (ctx->mask & (1 << (ctx->word[i] - 'a'))) {
                    result--;
                    break;
                }
                old = ctx->word[i];
                ctx->mask |= (1 << (ctx->word[i] - 'a'));
            }
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
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
