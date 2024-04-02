#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct context_t {
    int n;
};
struct context_t context;

#if 0
1 = 1
2 = 1 + 1
3 = 1 + 1 + 1
4 = 4
5 = 4 + 1
6 = 4 + 1 + 1
7 = 4 + 1 + 1 + 1
8 = 8
9 = 9
10 = 9 + 1
11 = 9 + 1 + 1
12 = 8 + 4
13 = 8 + 4 + 1
14 = 8 + 4 + 1 + 1
15 = 9 + 4 + 1 + 1
16 = 8 + 8
17 = 9 + 8
18 = 9 + 9
19 = 9 + 9 + 1
20 = 9 + 9 + 1 + 1
21 = 9 + 8 + 4
22 = 9 + 8 + 4 + 1
23 = 9 + 9 + 4 + 1
24 = 8 + 8 + 8
25 = 25
#endif

int get_count(int n)
{
    int loop[4];
    int value[4];

    loop[0] = sqrt(n);
    for (; loop[0] > 0; loop[0]--) {
        value[0] = n - loop[0] * loop[0];
        if (value[0] == 0) {
            return 1;
        }
        loop[1] = sqrt(value[0]);
        for (; loop[1] > 0; loop[1]--) {
            value[1] = value[0] - loop[1] * loop[1];
            if (value[1] == 0) {
                return 2;
            }
            loop[2] = sqrt(value[1]);
            for (; loop[2] > 0; loop[2]--) {
                value[2] = value[1] - loop[2] * loop[2];
                if (value[2] == 0) {
                    return 3;
                }
                loop[3] = sqrt(value[2]);
                for (; loop[3] > 0; loop[3]--) {
                    value[3] = value[2] - loop[3] * loop[3];
                    if (value[3] == 0) {
                        return 4;
                    }
                }
            }
        }
    }
    return 5;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = get_count(ctx->n);
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
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
