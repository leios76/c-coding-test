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
    uint64_t map[64];
};
struct context_t context;
char board[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
char modified[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int get_count(struct context_t * ctx, int x, int y)
{
    uint64_t mask1 = 0xAAAAAAAAAAAAAAAAULL;
    uint64_t mask2 = 0x5555555555555555ULL;
    uint64_t value;

    int min_count = 0xFFFFF;
    int count = 0;

    count = 0;

    for (int n = 0; n < 8; n++) {
        if ((n % 2) == 0) {
            value = ctx->map[y + n] ^ mask1;
        } else {
            value = ctx->map[y + n] ^ mask2;
        }
        for (int b = 0; b < 8; b++) {
            if (ctx->map[y + n] & (1ULL << x + b)) {
                board[b] = '1';
            } else {
                board[b] = '0';
            }
            if (value & (1ULL << (x + b))) {
                count++;
                modified[b] = 'x';
            } else {
                modified[b] = '_';
            }
        }
        debug("[%2d,%2d] board: %s modify: %s => %d\n", x, n + y, board, modified, count);
    }
    debug("    [%2d,%2d] ==> %d\n", x, y, count);
    if (min_count > count) {
        min_count = count;
    }

    count = 0;
    for (int n = 0; n < 8; n++) {
        if ((n % 2) != 0) {
            value = ctx->map[y + n] ^ mask1;
        } else {
            value = ctx->map[y + n] ^ mask2;
        }
        for (int b = 0; b < 8; b++) {
            if (ctx->map[y + n] & (1ULL << x + b)) {
                board[b] = '1';
            } else {
                board[b] = '0';
            }
            if (value & (1ULL << (x + b))) {
                count++;
                modified[b] = 'x';
            } else {
                modified[b] = '_';
            }
        }
        debug("[%2d,%2d] board: %s modify: %s => %d\n", x, n + y, board, modified, count);
    }
    debug("    [%2d,%2d] ==> %d\n", x, y, count);
    if (min_count > count) {
        min_count = count;
    }

    return min_count;
}

void solve(struct context_t * ctx)
{
    int result = 0xFFFFF;
    int count;
    for (int n = 0; n < ctx->n - 7; n++) {
        for (int m = 0; m < ctx->m - 7; m++) {
            count = get_count(ctx, m, n);
            if (result > count) {
                result = count;
            }
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    char line[52];
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->n, &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", line);
        for (int m = 0; m < ctx->m; m++) {
            if (line[m] == 'W') {
                ctx->map[n] |= (1ULL << m);
            }
        }
    }
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
