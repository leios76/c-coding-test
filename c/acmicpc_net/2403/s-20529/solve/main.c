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
    int mbti_count[16];
    int max_count;
};
struct context_t context;

int mbti_distance_table[16][16];

int get_min_distance(struct context_t * ctx, int mask1, int mask2, int depth)
{
    int min_distance = 0x7FFFFFF;
    int distance;
    for (int i = 0; i < 16; i++) {
        if (ctx->mbti_count[i] == 0) {
            continue;
        }
        if (depth == 0) {
            distance = get_min_distance(ctx, i, mask2, depth + 1);
            if (min_distance > distance) {
                min_distance = distance;
            }
        } else if (depth == 1) {
            if (ctx->mbti_count[i] == 1 && mask1 == i) {
                continue;
            }
            distance = get_min_distance(ctx, mask1, i, depth + 1);
            if (min_distance > distance) {
                min_distance = distance;
            }
        } else if (depth == 2) {
            if (ctx->mbti_count[i] == 1 && (mask1 == i || mask2 == i)) {
                continue;
            }
            if (ctx->mbti_count[i] == 2 && (mask1 == i && mask2 == i)) {
                continue;
            }
            distance = mbti_distance_table[mask1][mask2] + mbti_distance_table[mask2][i] + mbti_distance_table[mask1][i];
            if (min_distance > distance) {
                min_distance = distance;
            }
        }
    }
    return min_distance;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = get_min_distance(ctx, 0, 0, 0);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    char mbti[5];
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", mbti);
        int mbti_value = 0;
        if (mbti[0] == 'E') {
            mbti_value |= 0x08;
        }
        if (mbti[1] == 'N') {
            mbti_value |= 0x04;
        }
        if (mbti[2] == 'F') {
            mbti_value |= 0x02;
        }
        if (mbti[3] == 'P') {
            mbti_value |= 0x01;
        }
        ctx->mbti_count[mbti_value]++;
        if (ctx->max_count < ctx->mbti_count[mbti_value]) {
            ctx->max_count = ctx->mbti_count[mbti_value];
        }
    }
}

int main(int argc, char ** argv)
{
    int t = 1;


    for (int j = 0; j < 16; j++) {
        for (int i = 0; i < 16; i++) {
            int d = i ^ j;
            int c = 0;
            for (int b = 0; b < 4; b++) {
                if (d & (1 << b)) {
                    c++;
                }
            }
            mbti_distance_table[j][i] = c;
        }
    }
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }
    return 0;
}
