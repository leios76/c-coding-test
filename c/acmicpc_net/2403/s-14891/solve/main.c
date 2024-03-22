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
    uint8_t gear[4];
    int k;
    int target[100];
    int direction[100];
};
struct context_t context;

int rotate(uint8_t gear, int direction)
{
    uint8_t temp;
    if (direction == 1) {
        temp = (gear >> 7) & 0x01;
        gear <<= 1;
        gear |= temp;
    } else if (direction == -1) {
        temp = (gear << 7) & 0x80;
        gear >>= 1;
        gear |= temp;
    }
    return gear;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    int direction;
    uint8_t prev_gear;
    if (ctx->gear[0] == 0xFF && ctx->gear[1] == 0xFF && ctx->gear[2] == 0xFF && ctx->gear[3] == 0xFF) {
        printf("15\n");
        return;
    }

    if (ctx->gear[0] == 0 && ctx->gear[1] == 0 && ctx->gear[2] == 0 && ctx->gear[3] == 0) {
        printf("0\n");
        return;
    }

    for (int k = 0; k < ctx->k; k++) {
        direction = ctx->direction[k];
        // right gears
        prev_gear = ctx->gear[ctx->target[k] - 1];
        for (int i = ctx->target[k]; i < 4; i++) {
            int left = (prev_gear >> 2) & 0x01;
            int right = (ctx->gear[i] >> 6) & 0x01;
            prev_gear = ctx->gear[i];
            if (left == right) {
                break;
            }
            direction *= -1;
            ctx->gear[i] = rotate(ctx->gear[i], direction);
        }

        direction = ctx->direction[k];
        // left gears
        prev_gear = ctx->gear[ctx->target[k] - 1];
        for (int i = ctx->target[k] - 2; i >= 0; i--) {
            int right = (prev_gear >> 6) & 0x01;
            int left = (ctx->gear[i] >> 2) & 0x01;
            prev_gear = ctx->gear[i];
            if (left == right) {
                break;
            }
            direction *= -1;
            ctx->gear[i] = rotate(ctx->gear[i], direction);
        }

        // target gear
        ctx->gear[ctx->target[k] - 1] = rotate(ctx->gear[ctx->target[k] - 1], ctx->direction[k]);
    }
    for (int i = 3; i >= 0; i--) {
        result = result * 2 + (ctx->gear[i] & 0x01);
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    char line[9];
    memset(ctx, 0, sizeof(struct context_t));
    for (int i = 0; i < 4; i++) {
        scanf("%s", line);
        for (int j = 0; j < 8; j++) {
            ctx->gear[i] |= (line[j] - '0') << j;
        }
    }
    scanf("%d", &ctx->k);
    for (int k = 0; k < ctx->k; k++) {
        scanf("%d%d\n", &ctx->target[k], &ctx->direction[k]);
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
