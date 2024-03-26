#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif


struct wear_t {
    int name;
    int type;
};

struct context_t {
    int n;
    char name_list[30][21];
    char type_list[30][21];

    int name_count;
    int type_count;

    struct wear_t wear[30];
    int wear_count;
};
struct context_t context;

int get_case_count(struct context_t * ctx, int start, uint32_t mask)
{
    int count = 0;
    for (int w = start; w < ctx->wear_count; w++) {
        if (mask & (1 << ctx->wear[w].type)) {
            continue;
        }
        count += 1 + get_case_count(ctx, w + 1, mask | (1 << ctx->wear[w].type));
    }
    return count;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    result = get_case_count(ctx, 0, 0);
    printf("%d\n", result);
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
        int ni = 0;
        for (ti = 0; ti < ctx->type_count; ti++) {
            if (strcmp(ctx->type_list[ti], type) == 0) {
                break;
            }
        }
        if (ti == ctx->type_count) {
            strcpy(ctx->type_list[ctx->type_count++], type);
        }
        for (ni = 0; ni < ctx->name_count; ni++) {
            if (strcmp(ctx->name_list[ni], name) == 0) {
                break;
            }
        }
        if (ni == ctx->name_count) {
            strcpy(ctx->name_list[ctx->name_count++], name);
        }
        ctx->wear[ctx->wear_count].name = ni;
        ctx->wear[ctx->wear_count].type = ti;
        ctx->wear_count++;
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
