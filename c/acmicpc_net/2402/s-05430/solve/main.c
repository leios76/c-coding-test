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
    char p[100001];
    int n;
    int x[100000];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    int start_index = 0;
    int end_index = ctx->n - 1;
    int direction = 1;
    int error = 0;
    for (int p = 0; p < strlen(ctx->p); p++) {
        switch (ctx->p[p]) {
        case 'R':
            direction = !direction;
            break;
        case 'D':
            if (direction) {
                start_index++;
            } else {
                end_index--;
            }
            debug("%d ~ %d\n", start_index, end_index);
            if (end_index - start_index + 1 < 0) {
                error = 1;
            }
            break;
        }
    }
    if (error) {
        printf("error\n");
    } else {
        printf("[");
        if (direction) {
            for (int i = start_index; i <= end_index; i++) {
                if (i == end_index) {
                    printf("%d", ctx->x[i]);
                } else {
                    printf("%d,", ctx->x[i]);
                }
            }
        } else {
            for (int i = end_index; i >= start_index; i--) {
                if (i == start_index) {
                    printf("%d", ctx->x[i]);
                } else {
                    printf("%d,", ctx->x[i]);
                }
            }
        }
        printf("]\n");
    }
}

char line[100000 * 110];
void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%s", ctx->p);
    scanf("%d", &ctx->n);
    scanf("%s", line);
    line[0] = '0';
    line[strlen(line) - 1] = 0;
    char * ptr = strtok(line, ",");
    for (int n = 0; n < ctx->n; n++) {
        ctx->x[n] = atoi(ptr);
        ptr = strtok(NULL, ",");
        if (ptr == NULL) {
            break;
        }
    }
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
