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
    int l;
    char line[51];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;
    uint64_t hash = 0;
    uint64_t hash_sum = 0;
    int salt = 1234567891;
    int multi = 31;

    for (int l = 0; l < ctx->l; l++) {
        hash = ctx->line[l] - 'a' + 1;
        for (int i = 0; i < l; i++) {
            hash = hash * 31;
            while (hash > salt) {
                hash -= salt;
            }
        }
        hash_sum += hash;
        while (hash_sum > salt) {
            hash_sum -= salt;
        }
    }

    printf("%lu\n", hash_sum);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->l);
    scanf("%s", ctx->line);
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
