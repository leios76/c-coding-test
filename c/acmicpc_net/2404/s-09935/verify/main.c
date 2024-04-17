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
    char line[2][1000001];
    char keyword[37];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    char * str;
    int buffer_index = 0;
    int next_buffer_index = 0;
    while (1) {
        str = strstr(ctx->line[buffer_index], ctx->keyword);
        if (str == NULL) {
            break;
        }
        next_buffer_index = (buffer_index + 1) % 2;
        memcpy(ctx->line[next_buffer_index], ctx->line[buffer_index], str - ctx->line[buffer_index]);
        memcpy(&ctx->line[next_buffer_index][str - ctx->line[buffer_index]], str + strlen(ctx->keyword), strlen(str) - strlen(ctx->keyword) + 1);
        buffer_index = next_buffer_index;
    }

    if (strlen(ctx->line[buffer_index]) == 0) {
        printf("FLURA\n");
    } else {
        printf("%s\n", ctx->line[buffer_index]);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%s", ctx->line[0]);
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
