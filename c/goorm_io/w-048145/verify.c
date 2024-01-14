#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct stage_t {
    int * area[2048 * 2048];
    int edge_list[2048 * 2048];
    int edge_count;
};

struct context_t {
    int n;
    int k;
    uint64_t bitmap[2048 * 2048 / 64];
    int culture_x[100000];
    int culture_y[100000];
    int culture_count;

    struct stage_t stages[2];
    int culture_id[100000];

    int curr_stage_index;
    int next_stage_index;
};

int find_culture(struct context_t * context, int a)
{
    if (context->culture_id[a] == a) {
        return a;
    }
    context->culture_id[a] = find_culture(context, context->culture_id[a]);
    return context->culture_id[a];
}

int union_culture(struct context_t * context, int a, int b)
{
    a = find_culture(context, a);
    b = find_culture(context, b);

    context->culture_id[b] = a;
}

int check_culture(struct context_t * context, int src, int dest) {
    struct stage_t * curr = &context->stages[context->curr_stage_index];
    struct stage_t * next = &context->stages[context->next_stage_index];
    if (next->area[dest] != 0) {
        if (*next->area[dest] != *curr->area[src]) {
            if (*next->area[dest] < *curr->area[src]) {
#ifdef DEBUG_OUTPUT
                printf("(%d,%d %d) (%d,%d %d) culture %d is combined\n", src % 2048, src / 2048, *curr->area[src], dest % 2048, dest / 2048, *next->area[dest], *curr->area[src]);
#endif
                int temp = *curr->area[src];
                for (int i = 0; i < context->culture_count; i++) {
                    if (context->culture_id[i] == temp) {
                        context->culture_id[i] = *next->area[dest];
                    }
                }
                return 1;
            } else {
#ifdef DEBUG_OUTPUT
                printf("(%d,%d %d) (%d,%d %d) culture %d is combined\n", src % 2048, src / 2048, *curr->area[src], dest % 2048, dest / 2048, *next->area[dest], *next->area[dest]);
#endif
                int temp = *next->area[dest];
                for (int i = 0; i < context->culture_count; i++) {
                    if (context->culture_id[i] == temp) {
                        context->culture_id[i] = *curr->area[src];
                    }
                }
                return 1;
            }
        }
    }
    return 0;
}

int spread_culture(struct context_t * context, struct stage_t * curr, struct stage_t * next, int x, int y)
{
    int count = 0;
    int src = y*2048 + x;
    int dest;
    if (x > 0) {
        if (check_culture(context, src, src - 1)) {
            count++;
        }
    }
    if (x < context->n - 1) {
        if (check_culture(context, src, src + 1)) {
            count++;
        }
    }
    if (y > 0) {
        if (check_culture(context, src, src - 2048)) {
            count++;
        }
    }
    if (y < context->n - 1) {
        if (check_culture(context, src, src + 2048)) {
            count++;
        }
    }

    return count;
}

int fill_culture(struct context_t * context, int src, int dest) {
    struct stage_t * curr = &context->stages[context->curr_stage_index];
    struct stage_t * next = &context->stages[context->next_stage_index];

    if (next->area[dest] == 0) {
        next->area[dest] = curr->area[src];
        next->edge_list[next->edge_count++] = dest;
    }
    return 0;
}

void fill_around(struct context_t * context, struct stage_t * curr, struct stage_t * next, int x, int y)
{
    int count = 0;
    int src = y*2048 + x;
    int dest;
    if (x > 0) {
        fill_culture(context, src, src - 1);
    }
    if (x < context->n - 1) {
        fill_culture(context, src, src + 1);
    }
    if (y > 0) {
        fill_culture(context, src, src - 2048);
    }
    if (y < context->n - 1) {
        fill_culture(context, src, src + 2048);
    }
}

int verify(struct context_t * context)
{
    int turn;

    turn = 0;
    while (context->k > 1) {
        context->next_stage_index = (context->curr_stage_index + 1) % 2;
        memcpy(context->stages[context->next_stage_index].area, context->stages[context->curr_stage_index].area, sizeof(context->stages[context->next_stage_index].area));
        memset(context->stages[context->next_stage_index].edge_list, 0, sizeof(context->stages[context->next_stage_index].edge_list));
        context->stages[context->next_stage_index].edge_count = 0;

#if 0
#ifdef DEBUG_OUTPUT
        printf("[%d] culture\n", turn);
        for (int y = 0; y < context->n; y++) {
            for (int x = 0; x < context->n; x++) {
                if (context->stages[context->curr_stage_index].area[y*2048 + x] == 0) {
                    printf("0 ");
                } else {
                    printf("%d ", *context->stages[context->curr_stage_index].area[y*2048 + x]);
                }
            }
            printf("\n");
        }
        printf("\n");

#endif
#endif
        for (int j = 0; j < context->stages[context->curr_stage_index].edge_count; j++) {
            context->k -= spread_culture(context, &context->stages[context->curr_stage_index], &context->stages[context->next_stage_index], context->stages[context->curr_stage_index].edge_list[j] % 2048, context->stages[context->curr_stage_index].edge_list[j] / 2048);
        }

        if (context->k == 1) {
            break;
        }

        for (int j = 0; j < context->stages[context->curr_stage_index].edge_count; j++) {
            fill_around(context, &context->stages[context->curr_stage_index], &context->stages[context->next_stage_index], context->stages[context->curr_stage_index].edge_list[j] % 2048, context->stages[context->curr_stage_index].edge_list[j] / 2048);
        }

        context->curr_stage_index = (context->curr_stage_index + 1) % 2;

        turn++;
    }
#if 0
#ifdef DEBUG_OUTPUT
        for (int y = 0; y < context->n; y++) {
            for (int x = 0; x < context->n; x++) {
                if (context->stages[context->next_stage_index].area[y*2048 + x] == 0) {
                    printf("0 ");
                } else {
                    printf("%d ", *context->stages[context->next_stage_index].area[y*2048 + x]);
                }
            }
            printf("\n");
        }
        printf("\n");
#endif
#endif
    return turn;
}
