#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct context_t {
    int n;
};
struct context_t context;

int solve(struct context_t * ctx)
{
    return 0;
}

void init_data(struct context_t * ctx)
{
printf("|\\_/|\n");
printf("|q p|   /}\n");
printf("( 0 )\"\"\"\\\n");
printf("|\"^\"`    |\n");
printf("||_/=\\\\__|\n");

    memset(ctx, 0, sizeof(struct context_t));
}

int main()
{
    init_data(&context);
    solve(&context);

    return 0;
}
