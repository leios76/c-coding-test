#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif


struct wear_type_t {
    char type[21];
    int count;
};

struct context_t {
    int n;

    struct wear_type_t type_list[30];
    int type_count;

    int wear_type[30];
    int wear_type_count;
};
struct context_t context;

int get_case_count(struct context_t * ctx)
{
    int count = 1;
    for (int t = 0; t < ctx->type_count; t++) {

        count *= (ctx->type_list[t].count + 1);
    }
    return count - 1;
}

void solve(struct context_t * ctx)
{
    printf("%d\n", get_case_count(ctx));
}

void init_data(struct context_t * ctx)
{
    char name[21];
    char type[21];

    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s%s", name, type);
        int ti = 0;
        for (ti = 0; ti < ctx->type_count; ti++) {
            if (strcmp(ctx->type_list[ti].type, type) == 0) {
                break;
            }
        }
        if (ti == ctx->type_count) {
            strcpy(ctx->type_list[ctx->type_count++].type, type);
        }
        ctx->type_list[ti].count++;
        ctx->wear_type[ctx->wear_type_count] = ti;
        ctx->wear_type_count++;
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
