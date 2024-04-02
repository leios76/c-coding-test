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
    int count[26];
    char line[1000001];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int state = 0;
    int length = strlen(ctx->line);
    for (int i = 0; i < length; i++) {
        if (ctx->line[i] >= 'A' && ctx->line[i] <= 'Z') {
            ctx->count[ctx->line[i] - 'A']++;
        }
        if (ctx->line[i] >= 'a' && ctx->line[i] <= 'z') {
            ctx->count[ctx->line[i] - 'a']++;
        }
    }
    int max_index = -1;
    int max_count = 0;
    int max_dup = 0;

    for (int i = 0; i < 26; i++) {
        if (ctx->count[i] > max_count) {
            max_dup = 0;
            max_count = ctx->count[i];
            max_index = i;
        } else if (ctx->count[i] == max_count) {
            max_dup++;
        }
    }
    if (max_dup > 0) {
        printf("?\n");
    } else {
        printf("%c\n", max_index + 'A');
    }
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
