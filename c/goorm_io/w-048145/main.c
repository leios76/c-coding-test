#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

//#define RANDOM_RUN

#ifdef RANDOM_RUN
int max_n = 2000;
int max_k = 10;
#endif

#define SECTOR_SIZE     16

struct stage_t {
    int * area[2048 * 2048];
    int edge_list[2048 * 2048];
    int edge_count;
};

struct context_t {
    int n;
    int k;
    uint16_t bitmap[2048 * 2048 / SECTOR_SIZE];
    int culture_x[100000];
    int culture_y[100000];
    int culture_count;

    struct stage_t stages[2];
    int culture_id[100000];

    int curr_stage_index;
    int next_stage_index;
};

struct context_t solve_context;
#ifdef RANDOM_RUN
struct context_t verify_context;
#endif

int find_nearest_culture(struct context_t * context, int x, int y, int min_distance)
{
    if (context->k == 1) {
        return 0;
    }

    for (int distance = min_distance; distance < 2000; distance++) {
        for (int dy = y - (distance * 2 + 1); dy <= y + (distance * 2 + 1); dy++) {
            for (int dx = x - (distance * 2 + 1); dx <= x + (distance * 2 + 1); dx++) {
                if (dx < 0 || dx >= context->n || dy < 0 || dy >= context->n || (dx == x && dy == y)) {
                    continue;
                }
                int c = dy * 2048 + dx;
                if ((context->bitmap[c/SECTOR_SIZE] & (1ULL << (c%SECTOR_SIZE))) && (abs(x - dx) + abs(y - dy))/2 <= distance) {
                    return distance;
                }
            }
        }
    }
    return 0;
}

int find_nearest_culture_in_sector(struct context_t * context, int x, int y, int start_x, int start_y, uint16_t value)
{
    int min_distance = 2048 * 2048;
    int distance;

    for (int i = 0; i < SECTOR_SIZE; i++) {
        if (value & (1ULL << i)) {
            int dx = start_x + i;
            distance = (abs(x - dx) + abs(y - start_y)) / 2;
#ifdef DEBUG_OUTPUT
            printf("get distance (%d,%d) - (%d,%d) = %d\n", x, y, dx, start_y, distance);
#endif
            if (min_distance > distance) {
                min_distance = distance;
            }
        }
    }

    return min_distance;
}


int find_sector_culture(struct context_t * context, int x, int y)
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int min_distance = 2048 * 2048;
    int distance = 2048 * 2048;

    if (context->k == 1) {
        return 0;
    }
    start_x = (int)(x / SECTOR_SIZE) * SECTOR_SIZE;
    start_y = (int)(y / SECTOR_SIZE) * SECTOR_SIZE;
    for (int r = 0; r < SECTOR_SIZE; r++) {
        if (start_y + r == y) {
            distance = find_nearest_culture_in_sector(context, x, y, start_x, start_y + r, context->bitmap[((start_y + r) * 2048 + start_x)/SECTOR_SIZE] & ~(1ULL << (x % SECTOR_SIZE)));
        } else {
            if (context->bitmap[((start_y + r) * 2048 + start_x)/SECTOR_SIZE] > 0) {
                distance = find_nearest_culture_in_sector(context, x, y, start_x, start_y + r, context->bitmap[((start_y + r) * 2048 + start_x)/SECTOR_SIZE]);
            }
        }
        if (min_distance > distance) {
            min_distance = distance;
        }
    }
#ifdef DEBUG_OUTPUT
    printf("find %d, %d sector (0) => %d\n", start_x, start_y, min_distance);
#endif

    int around_x[4] = { -1, 0, 1, 0 };
    int around_y[4] = { 0, -1, 0, 1 };
    for (int sector = 1; sector < 2048 / SECTOR_SIZE; sector++) {
        start_x = (int)(x / SECTOR_SIZE - sector) * SECTOR_SIZE;
        start_y = (int)(y / SECTOR_SIZE - sector) * SECTOR_SIZE;
        end_x = (int)(x / SECTOR_SIZE + sector) * SECTOR_SIZE;
        end_y = (int)(y / SECTOR_SIZE - sector) * SECTOR_SIZE;
        for (int dy = start_y; dy <= end_y; dy+=SECTOR_SIZE) {
            for (int dx = start_x; dx <= end_x; dx+=SECTOR_SIZE) {
                if (dx < 0 || dy < 0 || dx >= context->n || dy >= context->n) {
                    continue;
                }
                for (int r = 0; r < SECTOR_SIZE; r++) {
                    if (context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE] > 0) {
                        distance = find_nearest_culture_in_sector(context, x, y, dx, dy + r, context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE]);
                        if (min_distance > distance) {
                            min_distance = distance;
                        }
                    }
                }
            }
        }
#ifdef DEBUG_OUTPUT
        printf("find %d, %d sector (%d) => %d\n", start_x, start_y, sector, min_distance);
#endif

        start_x = (int)(x / SECTOR_SIZE + sector) * SECTOR_SIZE;
        start_y = (int)(y / SECTOR_SIZE - sector) * SECTOR_SIZE;
        end_x = (int)(x / SECTOR_SIZE + sector) * SECTOR_SIZE;
        end_y = (int)(y / SECTOR_SIZE + sector) * SECTOR_SIZE;
        for (int dy = start_y; dy <= end_y; dy+=SECTOR_SIZE) {
            for (int dx = start_x; dx <= end_x; dx+=SECTOR_SIZE) {
                if (dx < 0 || dy < 0 || dx >= context->n || dy >= context->n) {
                    continue;
                }
                for (int r = 0; r < SECTOR_SIZE; r++) {
                    if (context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE] > 0) {
                        distance = find_nearest_culture_in_sector(context, x, y, dx, dy + r, context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE]);
                        if (min_distance > distance) {
                            min_distance = distance;
                        }
                    }
                }
            }
        }
#ifdef DEBUG_OUTPUT
        printf("find %d, %d sector (%d) => %d\n", start_x, start_y, sector, min_distance);
#endif

        start_x = (int)(x / SECTOR_SIZE - sector) * SECTOR_SIZE;
        start_y = (int)(y / SECTOR_SIZE + sector) * SECTOR_SIZE;
        end_x = (int)(x / SECTOR_SIZE + sector) * SECTOR_SIZE;
        end_y = (int)(y / SECTOR_SIZE + sector) * SECTOR_SIZE;
        for (int dy = start_y; dy <= end_y; dy+=SECTOR_SIZE) {
            for (int dx = start_x; dx <= end_x; dx+=SECTOR_SIZE) {
                if (dx < 0 || dy < 0 || dx >= context->n || dy >= context->n) {
                    continue;
                }
                for (int r = 0; r < SECTOR_SIZE; r++) {
                    if (context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE] > 0) {
                        distance = find_nearest_culture_in_sector(context, x, y, dx, dy + r, context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE]);
                        if (min_distance > distance) {
                            min_distance = distance;
                        }
                    }
                }
            }
        }
#ifdef DEBUG_OUTPUT
        printf("find %d, %d sector (%d) => %d\n", start_x, start_y, sector, min_distance);
#endif

        start_x = (int)(x / SECTOR_SIZE - sector) * SECTOR_SIZE;
        start_y = (int)(y / SECTOR_SIZE - sector) * SECTOR_SIZE;
        end_x = (int)(x / SECTOR_SIZE - sector) * SECTOR_SIZE;
        end_y = (int)(y / SECTOR_SIZE + sector) * SECTOR_SIZE;
        for (int dy = start_y; dy <= end_y; dy+=SECTOR_SIZE) {
            for (int dx = start_x; dx <= end_x; dx+=SECTOR_SIZE) {
                if (dx < 0 || dy < 0 || dx >= context->n || dy >= context->n) {
                    continue;
                }
                for (int r = 0; r < SECTOR_SIZE; r++) {
                    if (context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE] > 0) {
                        distance = find_nearest_culture_in_sector(context, x, y, dx, dy + r, context->bitmap[((dy + r) * 2048 + dx)/SECTOR_SIZE]);
                        if (min_distance > distance) {
                            min_distance = distance;
                        }
                    }
                }
            }
        }
#ifdef DEBUG_OUTPUT
        printf("find %d, %d sector (%d) => %d\n", start_x, start_y, sector, min_distance);
#endif
        if (min_distance < 2048*2048) {
            return min_distance;
        }
    }

#ifdef DEBUG_OUTPUT
    printf("not found\n");
#endif
    return 0;
}
int solve(struct context_t * context)
{
    int max_distance = 0;
    int distance;
    for (int i = 0; i < context->culture_count; i++) {
        distance = find_sector_culture(context, context->culture_x[i], context->culture_y[i]);
        if (max_distance < distance) {
            max_distance = distance;
        }
#ifdef DEBUG_OUTPUT
        printf("[%d] %d, %d -- %d\n", i + 1, context->culture_x[i], context->culture_y[i], distance);
#endif
    }

    return max_distance;
}

int main()
{
    int x;
    int y;

    memset(&solve_context, 0, sizeof(solve_context));
#ifdef RANDOM_RUN
    memset(&verify_context, 0, sizeof(verify_context));
#endif

#ifdef RANDOM_RUN
    srand(time(NULL));
    verify_context.n = rand() % (max_n - 1) + 2;
    verify_context.k = rand() % max_k + 1;
    solve_context.n = verify_context.n;
    solve_context.k = verify_context.k;
#else
    scanf("%d %d", &solve_context.n, &solve_context.k);
#endif

    solve_context.culture_count = solve_context.k;
    solve_context.curr_stage_index = 0;
    solve_context.next_stage_index = 1;
#ifdef RANDOM_RUN
    verify_context.culture_count = verify_context.k;
    verify_context.curr_stage_index = 0;
    verify_context.next_stage_index = 1;
#endif

    for (int i = 1; i <= solve_context.culture_count; i++) {
#ifdef RANDOM_RUN
        x = rand() % verify_context.n + 1;
        y = rand() % verify_context.n + 1;
#else
        scanf("%d %d", &x, &y);
#endif
#ifdef DEBUG_OUTPUT
        printf("[%d] %d, %d\n", i, x - 1, y - 1);
#endif

        int c = (y - 1) * 2048 + (x - 1);
        solve_context.bitmap[c/SECTOR_SIZE] |= (1ULL << (c%SECTOR_SIZE));
        solve_context.culture_x[i - 1] = x - 1;
        solve_context.culture_y[i - 1] = y - 1;
#ifdef RANDOM_RUN
        verify_context.culture_id[i - 1] = i;
        if (verify_context.stages[0].area[(y - 1) * 2048 + (x - 1)] != 0) {
            verify_context.k--;
        }
        verify_context.stages[0].area[(y - 1) * 2048 + (x - 1)] = &verify_context.culture_id[i - 1];
        verify_context.stages[0].edge_list[verify_context.stages[0].edge_count++] = (y - 1) * 2048 + (x - 1);
#endif
    }

    int solve_output = solve(&solve_context);
#ifdef RANDOM_RUN
    int verify_output = verify(&verify_context);
#endif

#ifdef RANDOM_RUN
    printf("%d %d\n", solve_output, verify_output);
#else
    printf("%d\n", solve_output);
#endif
    return 0;
}
