#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define SECTOR_SIZE     16

struct stage_t {
    int area[2048 * 2048];
    int edge_list[2048 * 2048];
    int edge_count;
};

struct context_t {
    int n;
    int k;
    int culture_count;

    struct stage_t stages[2];
    int culture_id[100001];

    int curr_stage_index;
    int next_stage_index;
};

struct context_t verify_context;

int findParent(struct context_t * context, int x)
{
    if (context->culture_id[x] == x) {
        return x;
    }
    context->culture_id[x] = findParent(context, context->culture_id[x]);
    return context->culture_id[x];
}

int check_culture(struct context_t * context, int src, int dest) {
    struct stage_t * curr = &context->stages[context->curr_stage_index];
    struct stage_t * next = &context->stages[context->next_stage_index];
    int root_src;
    int root_dest;
    if (next->area[dest] != 0) {
        root_src = findParent(context, curr->area[src]);
        root_dest = findParent(context, next->area[dest]);
        if (root_dest != root_src) {
            if (root_dest < root_src) {
#ifdef DEBUG_OUTPUT
                printf("(%d,%d %d) (%d,%d %d) culture %d is combined\n", src % 2048, src / 2048, root_src, dest % 2048, dest / 2048, root_dest, root_src);
#endif
                context->culture_id[root_src] = root_dest;
                return 1;
            } else {
#ifdef DEBUG_OUTPUT
                printf("(%d,%d %d) (%d,%d %d) culture %d is combined\n", src % 2048, src / 2048, root_src, dest % 2048, dest / 2048, root_dest, root_dest);
#endif
                context->culture_id[root_dest] = root_src;
                return 1;
            }
        }
    }
    return 0;
}

int spread_culture(struct context_t * context, int x, int y)
{
    int count = 0;
    int src = y*2048 + x;
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

void fill_around(struct context_t * context, int x, int y)
{
    int src = y*2048 + x;
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
            context->k -= spread_culture(context, context->stages[context->curr_stage_index].edge_list[j] % 2048, context->stages[context->curr_stage_index].edge_list[j] / 2048);
        }

        if (context->k == 1) {
            break;
        }

        for (int j = 0; j < context->stages[context->curr_stage_index].edge_count; j++) {
            fill_around(context, context->stages[context->curr_stage_index].edge_list[j] % 2048, context->stages[context->curr_stage_index].edge_list[j] / 2048);
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

int main()
{
    int x;
    int y;

    memset(&verify_context, 0, sizeof(verify_context));

    scanf("%d %d", &verify_context.n, &verify_context.k);
#ifdef DEBUG_OUTPUT
    printf("%d %d\n", verify_context.n, verify_context.k);
#endif
    verify_context.culture_count = verify_context.k;
    verify_context.curr_stage_index = 0;
    verify_context.next_stage_index = 1;

    for (int i = 1; i <= verify_context.culture_count; i++) {
        int ix;
        int iy;
        scanf("%d %d", &ix, &iy);
        x = ix - 1;
        y = iy - 1;
#ifdef DEBUG_OUTPUT
        printf("%d %d, %d %d\n", x, y, (x)/64, (y)/64);
#endif

        verify_context.culture_id[i] = i;
        if (verify_context.stages[0].area[(y) * 2048 + (x)] != 0) {
            verify_context.k--;
        }
        verify_context.stages[0].area[(y) * 2048 + (x)] = i;
        verify_context.stages[0].edge_list[verify_context.stages[0].edge_count++] = (y) * 2048 + (x);
    }

    int verify_output = verify(&verify_context);

    printf("%d\n", verify_output);
    return 0;
}
