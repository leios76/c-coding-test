#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct entry_t {
    int parent;
    int left;
    int right;
};

struct context_t {
    int n;
    struct entry_t entries[26];
};
struct context_t context;

void print_preorder(struct context_t * ctx, int index)
{
    printf("%c", 'A' + index);
    if (ctx->entries[index].left > -1) {
        print_preorder(ctx, ctx->entries[index].left);
    }
    if (ctx->entries[index].right > -1) {
        print_preorder(ctx, ctx->entries[index].right);
    }
}

void print_inorder(struct context_t * ctx, int index)
{
    if (ctx->entries[index].left > -1) {
        print_inorder(ctx, ctx->entries[index].left);
    }
    printf("%c", 'A' + index);
    if (ctx->entries[index].right > -1) {
        print_inorder(ctx, ctx->entries[index].right);
    }
}

void print_postorder(struct context_t * ctx, int index)
{
    if (ctx->entries[index].left > -1) {
        print_postorder(ctx, ctx->entries[index].left);
    }
    if (ctx->entries[index].right > -1) {
        print_postorder(ctx, ctx->entries[index].right);
    }
    printf("%c", 'A' + index);
}

void solve(struct context_t * ctx)
{
    print_preorder(ctx, 0);
    printf("\n");

    print_inorder(ctx, 0);
    printf("\n");

    print_postorder(ctx, 0);
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    char node[3][3];
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->entries, -1, sizeof(ctx->entries));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s%s%s", node[0], node[1], node[2]);
        int p = node[0][0] - 'A';
        int l = node[1][0] - 'A';
        int r = node[2][0] - 'A';
        if (l > -1) {
            ctx->entries[p].left = l;
            ctx->entries[l].parent = p;
        }
        if (r > -1) {
            ctx->entries[p].right = r;
            ctx->entries[r].parent = p;
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
