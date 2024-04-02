#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
};
struct context_t context;

int case_list[2][8] = { { 1, 1, 1, 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 } };

int solve(struct context_t * ctx)
{
    int i = 0;
    for (i = 0; i < ctx->n; i++) {
        case_list[(i + 1) % 2][0] = (case_list[i % 2][0] + case_list[i % 2][1] + case_list[i % 2][2] + case_list[i % 2][4] + case_list[i % 2][5]) % 100000007;
        case_list[(i + 1) % 2][1] = (case_list[i % 2][0] + case_list[i % 2][2] + case_list[i % 2][4]) % 100000007;
        case_list[(i + 1) % 2][2] = (case_list[i % 2][0] + case_list[i % 2][1] + case_list[i % 2][4] + case_list[i % 2][5]) % 100000007;
        case_list[(i + 1) % 2][4] = (case_list[i % 2][0] + case_list[i % 2][1] + case_list[i % 2][2]) % 100000007;
        case_list[(i + 1) % 2][5] = (case_list[i % 2][0] + case_list[i % 2][2]) % 100000007;
    }
    return case_list[i % 2][0];
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d", &ctx->n);
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
