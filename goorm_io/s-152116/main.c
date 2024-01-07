#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#define DEBUG_RUN
//#define DEBUG_OUTPUT


uint64_t bitmap1[2 * (1024 * 1024 + 262143) / 262144];
uint64_t bitmap2[2 * (1024 * 1024 + 4095) / 4096];
uint64_t bitmap3[2 * (1024 * 1024 + 63) / 64];


struct map_context_t {
    int width;
    int height;

    int width_shift;
    int height_shift;

    uint8_t * priority_map;
    uint64_t cur_pos;
};

void setbit(int priority, int x, int y, int w_b, int h_b)
{
    uint64_t index = (priority << (w_b + h_b)) | (y << h_b) | x;
    bitmap1[index / 262144] |= (1ULL << ((index / 4096) % 64));
    bitmap2[index / 4096] |= (1ULL << ((index / 64) % 64));
    bitmap3[index / 64] |= (1ULL << (index % 64));

#ifdef DEBUG_OUTPUT
    printf("set bitmap1 index %ld, mask(%ld) 0x%016llX\n", index / 262144, ((index / 4096) % 64), (1ULL << ((index / 4096) % 64)));
    printf("set bitmap2 index %ld, mask(%ld) 0x%016llX\n", index / 4096, ((index / 64) % 64), (1ULL << ((index / 64) % 64)));
    printf("set bitmap3 index %ld, mask(%ld) 0x%016llX\n", index / 64, (index % 64), (1ULL << (index % 64)));
#endif
}

uint64_t get_index(int w_b, int h_b)
{
    uint64_t index = 0;
    int bitmap1_size = 2 * (1024 * 1024 + 262143) / 262144;
    int i;
    int j;
    int k;
    int i_b;
    int j_b;
    int k_b;

    for (k = 0; k < bitmap1_size; k++) {
        if (bitmap1[k] == 0) {
            continue;
        }
        for (k_b = 0; k_b < 64; k_b++) {
            if (bitmap1[k] & (1ULL << k_b)) {
#ifdef DEBUG_OUTPUT
                printf("get bitmap1 index %d, mask(%d) 0x%016llX\n", k, k_b, (1ULL << k_b));
#endif
                for (j_b = 0; j_b < 64; j_b++) {
                    j = k * 64 + k_b;
                    if (bitmap2[j] & (1ULL << j_b)) {
#ifdef DEBUG_OUTPUT
                        printf("get bitmap2 index %d, mask(%d) 0x%016llX\n", j, j_b, (1ULL << j_b));
#endif
                        i = (k * 64 + k_b) * 64 + j_b;
                        for (i_b = 0; i_b < 64; i_b++) {
                            if (bitmap3[i] & (1ULL << i_b)) {
#ifdef DEBUG_OUTPUT
                                printf("get bitmap3 index %d, mask(%d) 0x%016llX\n", i, i_b, (1ULL << i_b));
#endif
                                index = ((k * 64 + k_b) * 64 + j_b) * 64 + i_b;
#ifdef DEBUG_OUTPUT
                                printf("index %lu, p %ld, y %ld, x %ld\n", index, (index >> (w_b + h_b)) & 0xFF, ((index >> h_b) & ((1 << w_b) - 1)), (index & ((1 << h_b) - 1)));
#endif
                                bitmap3[i] &= ~(1ULL << i_b);
#ifdef DEBUG_OUTPUT
                                printf("clear bitmap3 index %d, mask(%d) 0x%016llX\n", i, i_b, (1ULL << i_b));
#endif
                                if (bitmap3[i] == 0) {
#ifdef DEBUG_OUTPUT
                                    printf("clear bitmap2 index %d, mask(%d) 0x%016llX\n", j, j_b, (1ULL << j_b));
#endif
                                    bitmap2[j] &= ~(1ULL << j_b);
                                }
                                if (bitmap2[j] == 0) {
#ifdef DEBUG_OUTPUT
                                    printf("clear bitmap1 index %d, mask(%d) 0x%016llX\n", k, k_b, (1ULL << k_b));
#endif
                                    bitmap1[k] &= ~(1ULL << k_b);
                                }

                                return index;
                            }
                        }
                    }
                }
            }
        }
    }
    return -1;
}

void print_bits(int w_b, int h_b)
{
    int bitmap1_size = 2 * (1024 * 1024 + 262143) / 262144;
    for (int k = 0; k < bitmap1_size; k++) {
        if (bitmap1[k] == 0) {
            continue;
        }
        for (int j = k * 64; j < k * 64 + 64; j++) {
            if (bitmap2[j] == 0) {
                continue;
            }
            for (int i = j * 64; i < j * 64 + 64; i++) {
                if (bitmap3[i] == 0) {
                    continue;
                }
                for (int b = 0; b < 64; b++) {
                    if (bitmap3[i] & (1ULL << b)) {
#ifdef DEBUG_OUTPUT
                        uint64_t index;
                        index = i * 64 + b;
                        printf("index %lu(%d, %d, %d, %d) p %ld, y %ld, x %ld\n", index, k, j, i, b, (index >> (w_b + h_b)) & 0xFF, ((index >> h_b) & ((1 << w_b) - 1)), (index & ((1 << h_b) - 1)));
#endif
                    }
                }
            }
        }
    }
}

#ifdef DEBUG_RUN
void build_debug_spec(struct map_context_t * context)
{
    char line[1001];

    int w_line_count;
    int h_line_count;

    int x;
    int y;

    w_line_count = 4;
    h_line_count = 4;

    for (context->height_shift = 0; context->height_shift < 32; context->height_shift++) {
        if (w_line_count <= (1 << context->height_shift)) {
            context->height = (1 << context->height_shift);
            break;
        }
    }
    for (context->width_shift = 0; context->width_shift < 32; context->width_shift++) {
        if (h_line_count <= (1 << context->width_shift)) {
            context->width = (1 << context->width_shift);
            break;
        }
    }

    context->priority_map = (uint8_t *)malloc(context->width * context->height);
    memset(context->priority_map, 0xFF, context->width * context->height);

    for (y = 0; y < w_line_count; y++) {
        memset(line, 0, sizeof(line));
        switch (y) {
        case 0:
            strcpy(line, "P000"); break;
        case 1:
            strcpy(line, "PPPP"); break;
        case 2:
            strcpy(line, "000S"); break;
        case 3:
            strcpy(line, "0EP0"); break;
        }
        for (x = 0; x < h_line_count; x++) {
            switch (line[x]) {
            case '0':
                context->priority_map[(y << context->width_shift) | x] = 1;
                break;
            case 'P':
                context->priority_map[(y << context->width_shift) | x] = 0;
                break;
            case 'S':
                context->priority_map[(y << context->width_shift) | x] = 0x82;
                context->cur_pos = (y << context->width_shift) | x;
                break;
            case 'E':
                context->priority_map[(y << context->width_shift) | x] = 2;
                break;
            }
        }
    }
}
#endif

void build_spec(struct map_context_t * context)
{
    char line[1001];

    int w_line_count;
    int h_line_count;

    int x;
    int y;

    scanf("%d %d", &w_line_count, &h_line_count);

    for (context->height_shift = 0; context->height_shift < 32; context->height_shift++) {
        if (w_line_count <= (1 << context->height_shift)) {
            context->height = (1 << context->height_shift);
            break;
        }
    }
    for (context->width_shift = 0; context->width_shift < 32; context->width_shift++) {
        if (h_line_count <= (1 << context->width_shift)) {
            context->width = (1 << context->width_shift);
            break;
        }
    }

    context->priority_map = (uint8_t *)malloc(context->width * context->height);
    memset(context->priority_map, 0xFF, context->width * context->height);

    for (y = 0; y < w_line_count; y++) {
        memset(line, 0, sizeof(line));
        scanf("%s", line);
        for (x = 0; x < h_line_count; x++) {
            switch (line[x]) {
            case '0':
                context->priority_map[(y << context->width_shift) | x] = 1;
                break;
            case 'P':
                context->priority_map[(y << context->width_shift) | x] = 0;
                break;
            case 'S':
                context->priority_map[(y << context->width_shift) | x] = 0x82;
                context->cur_pos = (y << context->width_shift) | x;
                break;
            case 'E':
                context->priority_map[(y << context->width_shift) | x] = 2;
                break;
            }
        }
    }
}

int main()
{
    int candidate_x_diffs[4] = { -1, 0, 0, 1 };
    int candidate_y_diffs[4] = { 0, -1, 1, 0 };

    int total_danger = 0;

    uint64_t index;

    int x;
    int y;
    int base_x;
    int base_y;

    struct map_context_t context;
    memset(&context, 0, sizeof(context));

#ifdef DEBUG_RUN
    build_debug_spec(&context);
#else
    build_spec(&context);
#endif
    memset(bitmap1, 0, sizeof(bitmap1));
    memset(bitmap2, 0, sizeof(bitmap2));
    memset(bitmap3, 0, sizeof(bitmap3));

#ifdef DEBUG_OUTPUT
    printf("map: %dx%d\n", context.width, context.height);
#endif

#ifdef DEBUG_OUTPUT
    x = context.cur_pos & (context.width - 1);
    y = (context.cur_pos >> context.width_shift) & (context.height - 1);
    printf("start [%lu %d,%d p%02x]\n", context.cur_pos, y, x, context.priority_map[context.cur_pos]);
#endif
    context.priority_map[context.cur_pos] |= 0x80;

    while (1) {
        base_x = context.cur_pos & (context.width - 1);
        base_y = (context.cur_pos >> context.width_shift) & (context.height - 1);
        for (int c = 0; c < 4; c++) {
            x = base_x + candidate_x_diffs[c];
            y = base_y + candidate_y_diffs[c];
            if (x < 0 || x >= context.width || y < 0 || y >= context.height) {
                continue;
            }
            index = (y << context.width_shift) | x;
            if (context.priority_map[index] & 0x80) {
                continue;
            }
            int priority = context.priority_map[index] & 0x0F;

            if (priority == 2) {
                if (total_danger < 0) {
                    total_danger = 0;
                }
                printf("%d\n", total_danger);
                return 0;
            }

#ifdef DEBUG_OUTPUT
            printf("new candidate [%lu %d,%d p%d]\n", index, y, x, context.priority_map[index]);
#endif
            // priority에 0x10을 마스킹하여 다시 후보로 등록되지 않도록 한다.
            context.priority_map[index] |= 0x80;

            setbit(priority, x, y, context.height_shift, context.width_shift);
        }

#ifdef DEBUG_OUTPUT
        print_bits(context.height_shift, context.width_shift);
#endif
        index = get_index(context.height_shift, context.width_shift) & ((1 << (context.width_shift + context.height_shift)) - 1);
        int danger = 0;
        int priority = (context.priority_map[index] & 0x0F);
        if (priority == 0) {
            danger = -3;
        }

        base_x = index & (context.width - 1);
        base_y = (index >> context.width_shift) & (context.height - 1);

        for (int x_diff = -1; x_diff < 2; x_diff++) {
            for (int y_diff = -1; y_diff < 2; y_diff++) {
                x = base_x + x_diff;
                y = base_y + y_diff;
                if ((x == base_x && y == base_y) || x < 0 || x >= context.width || y < 0 || y >= context.height) {
                    continue;
                }

                if ((context.priority_map[(y << context.width_shift) + x] & 0x0F) == 0) {
                    danger++;
                }
            }
        }
#ifdef DEBUG_OUTPUT
        printf("move to %ld,%ld -> %ld,%ld add %d danger, total %d\n", ((context.cur_pos >> context.width_shift) & (context.height - 1)), (context.cur_pos & (context.height - 1)),
               ((index >> context.width_shift) & (context.height - 1)), (index & (context.width - 1)),
               danger, total_danger + danger);
#endif
        context.cur_pos = index;
        total_danger += danger;
    }

    if (total_danger < 0) {
        total_danger = 0;
    }
    printf("%d\n", total_danger);
    return 0;
}

