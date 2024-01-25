#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct coord_t {
    int x;
    int y;
    int score;
    int prev_index;
    int next_index;
};

struct context_t {
    int n;

    char command[1024];
    int scores[1024];

    struct coord_t coord_pool[1001];
    int head_index;
    int tail_index;
};
struct context_t context;

void print_list(struct context_t * c)
{
    int index = c->head_index;

    while (index > -1) {
        printf("[%d] %d <- %d,%d %d -> %d\n", index, c->coord_pool[index].prev_index, c->coord_pool[index].x, c->coord_pool[index].y, c->coord_pool[index].score, c->coord_pool[index].next_index);
        index = c->coord_pool[index].next_index;
    }
}

int find_index(struct context_t * c, int x, int y)
{
    int index = c->head_index;

    while (index > -1) {
        if (c->coord_pool[index].x == x && c->coord_pool[index].y == y) {
            return index;
        }
        index = c->coord_pool[index].next_index;
    }
    return -1;
}

int solve(struct context_t * c)
{
    int index;
    int x = 0;
    int y = 0;

    for (int i = 1; i <= c->n; i++) {
        int dx = 0;
        int dy = 0;
        switch (c->command[i - 1]) {
        case 'R':
            dx = 1;
            break;
        case 'U':
            dy = -1;
            break;
        case 'D':
            dy = 1;
            break;
        case 'L':
            dx = -1;
            break;
        }
        index = find_index(c, x + dx, y + dy);
#ifdef DEBUG_OUTPUT
        printf("find [%d] %d,%d ==> %d\n", i, x + dx, y + dy, index);
#endif
        c->coord_pool[i].x = x + dx;
        c->coord_pool[i].y = y + dy;

        if (index == -1) {
            c->coord_pool[i].prev_index = c->tail_index;
            c->coord_pool[i].next_index = -1;

            c->coord_pool[c->tail_index].next_index = i;
            c->tail_index = i;
        } else {
            if (index == c->head_index) {
                c->head_index = i;
                c->coord_pool[i].prev_index = -1;
            } else {
                c->coord_pool[c->coord_pool[index].prev_index].next_index = i;
                c->coord_pool[i].prev_index = c->coord_pool[index].prev_index;
            }
            c->tail_index = i;
            c->coord_pool[i].next_index = -1;
        }

#ifdef DEBUG_OUTPUT
        print_list(c);
#endif
        x += dx;
        y += dy;
    }

    int sum = 0;

    index = c->head_index;
    while (index > -1) {
        sum += c->coord_pool[index].score;
        index = c->coord_pool[index].next_index;
#ifdef DEBUG_OUTPUT
        printf("add %d,%d %d\n", c->coord_pool[index].x, c->coord_pool[index].y, c->coord_pool[index].score);
#endif
    }
    return sum;
}

int main()
{
    memset(&context, 0, sizeof(context));

    context.coord_pool[0].score = 1;
    context.coord_pool[0].next_index = -1;
    context.coord_pool[0].prev_index = -1;

    scanf("%d", &context.n);
    scanf("%s", context.command);
    for (int i = 1; i <= context.n; i++) {
        scanf("%d", &context.coord_pool[i].score);
    }

    printf("%d\n", solve(&context));

    return 0;
}
