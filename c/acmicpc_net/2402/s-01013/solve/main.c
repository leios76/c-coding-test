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
    int t;
    char line[1000][201];
};
struct context_t context;

int check_string(char * line, int length)
{
    int state = 0;
    int completed = 0;
    int repeat_count = 0;

    for (int i = 0; i < length; ) {
        switch (state) {
            case 0:
                if (memcmp(&line[i], "10", 2) == 0) {
                    state = 1;
                    i += 2;
                    completed = 0;
                } else if (memcmp(&line[i], "01", 2) == 0) {
                    state = 0;
                    i += 2;
                    completed = 1;
                } else {
                    return 0;
                }
                break;
            case 1:
                if (line[i] == '0') {
                    repeat_count++;
                    i++;
                } else {
                    if (repeat_count == 0) {
                        return 0;
                    }
                    repeat_count = 0;
                    state = 2;
                }
                break;
            case 2:
                if (line[i] == '1') {
                    if (repeat_count > 0 && memcmp(&line[i], "101", 3) == 0) {
                        state = 0;
                        i += 3;
                        completed = 1;
                    } else if (repeat_count > 0 && memcmp(&line[i], "100", 3) == 0) {
                        state = 1;
                        i += 3;
                        completed = 0;
                        repeat_count = 1;
                    } else {
                        completed = 1;
                        repeat_count++;
                        i++;
                    }
                } else {
                    if (repeat_count == 0) {
                        return 0;
                    }
                    repeat_count = 0;
                    state = 0;
                }
                break;
        }
    }
    return completed;
}

void solve(struct context_t * ctx)
{
    for (int t = 0; t < ctx->t; t++) {
        if (check_string(ctx->line[t], strlen(ctx->line[t]))) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->t);
    for (int t = 0; t < ctx->t; t++) {
        scanf("%s", ctx->line[t]);
    }
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
