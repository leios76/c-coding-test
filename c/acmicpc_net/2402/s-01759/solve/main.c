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
    int c;
    int cipher[15];
    int cipher_mask;
    int mo_mask;
    int ja_mask;
    int mask_remap[15];
};
struct context_t context;

void solve(struct context_t * ctx)
{
    int remap_index = 0;
    for (int i = 25; i >= 0; i--) {
        if (ctx->cipher_mask & (1 << i)) {
            switch (i + 'a') {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                ctx->mo_mask |= (1 << remap_index);
                break;
            default:
                ctx->ja_mask |= (1 << remap_index);
                break;
            }
            ctx->mask_remap[remap_index++] = i;
        }
    }

    for (int i = (1 << ctx->c) - 1; i > 0; i--) {
        int mo_mask = i & ctx->mo_mask;
        int ja_mask = i & ctx->ja_mask;
        int ch_count = 0;
        int ja_count = 0;
        int mo_count = 0;
        for (int b = 0; b < 27; b++) {
            if (i & (1 << b)) {
                ch_count++;
            }
        }
        if (ch_count != ctx->l) {
            continue;
        }
        for (int b = 0; b < 27; b++) {
            if (mo_mask & (1 << b)) {
                mo_count++;
            }
        }
        if (mo_count < 1) {
            continue;
        }
        for (int b = 0; b < 27; b++) {
            if (ja_mask & (1 << b)) {
                ja_count++;
            }
        }
        if (ja_count < 2) {
            continue;
        }

        //debug("ch %d, mo %d, ja %d, %06X & %06X = %06X \n", ch_count, mo_count, ja_count, i, ctx->mo_mask, mo_mask);
        for (int c = ctx->c - 1; c >= 0; c--) {
            if (i & (1 << c)) {
                printf("%c", ctx->mask_remap[c] + 'a');
            }
        }
        printf("\n");
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d%d", &ctx->l, &ctx->c);
    for (int c = 0; c < ctx->c; c++) {
        char ch[2];
        scanf("%s", ch);
        ctx->cipher[c] = ch[0];
        ctx->cipher_mask |= 1 << (ch[0] - 'a');
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
