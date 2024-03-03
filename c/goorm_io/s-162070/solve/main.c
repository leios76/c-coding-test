#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
    int k;
    int area[1002][1002];
    int x1[100000];
    int x2[100000];
    int y1[100000];
    int y2[100000];
};
struct context_t context;

int solve(struct context_t * ctx)
{
    int min_x = 1002;
    int min_y = 1002;
    int max_x = 0;
    int max_y = 0;
    for (int i = 0; i < ctx->n; i++) {
        ctx->area[ctx->y1[i]][ctx->x1[i]]++;
        ctx->area[ctx->y2[i]][ctx->x2[i]]++;

        ctx->area[ctx->y2[i]][ctx->x1[i]]--;
        ctx->area[ctx->y1[i]][ctx->x2[i]]--;
        if (min_x > ctx->x1[i]) {
            min_x = ctx->x1[i];
        }
        if (min_y > ctx->y1[i]) {
            min_y = ctx->y1[i];
        }
        if (max_x < ctx->x2[i]) {
            max_x = ctx->x2[i];
        }
        if (max_y < ctx->y2[i]) {
            max_y = ctx->y2[i];
        }
    }

    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            ctx->area[y][x + 1] += ctx->area[y][x];
        }
    }

    for (int x = min_x; x <= max_x; x++) {
        for (int y = min_y; y <= max_y; y++) {
            ctx->area[y + 1][x] += ctx->area[y][x];
        }
    }

    int sum = 0;
    for (int y = min_y; y <= max_y; y++) {
        for (int x = min_x; x <= max_x; x++) {
            if (ctx->area[y][x] == ctx->k) {
                sum++;
            }
        }
    }

    return sum;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d %d", &ctx->n, &ctx->k);
    for (int i = 0; i < ctx->n; i++) {
        scanf("%d %d %d %d", &ctx->x1[i], &ctx->y1[i], &ctx->x2[i], &ctx->y2[i]);
    }
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
