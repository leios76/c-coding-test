#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
    int value[5000];
    int usage[5000];
    int min_usage[5000];
    int changes[5000];
    int min_changes[5000];
};
struct context_t context;

int solve(struct context_t * ctx)
{
    int min_value = 0x7FFFFFFF;
    while (1) {
        int sum = 0;
        int curr[3] = { 0, 0, 0 };
        for (int i = 0; i < ctx->n; i++) {
            int m = (curr[ ctx->usage[i] ] - ctx->value[i] + 10) % 10;
            int p = (ctx->value[i] - curr[ ctx->usage[i] ] + 10) % 10;
            if (m < p) {
                sum += m;
                ctx->changes[i] = m;
                //printf("[%d] %d -> %d (%d)\n", ctx->usage[i], curr[ctx->usage[i]], ctx->value[i], m);
            } else {
                sum += p;
                ctx->changes[i] = p;
                //printf("[%d] %d -> %d (%d)\n", ctx->usage[i], curr[ctx->usage[i]], ctx->value[i], p);
            }
            curr[ctx->usage[i]] = ctx->value[i];
        }
        /*
        for (int j = 0; j < ctx->n; j++) {
            printf("%d ", ctx->usage[j]);
        }
        printf(" ==> %d\n", sum);
        */
        if (min_value > sum) {
            memcpy(ctx->min_usage, ctx->usage, sizeof(ctx->usage));
            memcpy(ctx->min_changes, ctx->changes, sizeof(ctx->changes));
            min_value = sum;
        }
        for (int i = 0; i < ctx->n; i++) {
            if (ctx->usage[i] < 2) {
                ctx->usage[i]++;
                break;
            }
            ctx->usage[i] = 0;
            if (i == ctx->n - 1) {
                for (int j = 0; j < ctx->n; j++) {
                    printf("%d ", ctx->min_usage[j]);
                }
                printf("\n");

                for (int j = 0; j < ctx->n; j++) {
                    printf("%d ", ctx->min_changes[j]);
                }
                printf("\n");

                return min_value;
            }
        }
    }
    return min_value;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->n);

    for (int i = 0; i < ctx->n; i++) {
        scanf("%d", &ctx->value[i]);
    }
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
