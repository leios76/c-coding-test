#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

struct stage_t {
    int edge_list[2048 * 2048];
    int edge_count;
};

struct context_t {
    int n;
    int k;

    int area[2048 * 2048];
    struct stage_t stages[2];
    int culture_id[100001];

    int turn;
};

struct context_t context;

int findParent(struct context_t * c, int x)
{
    if (c->culture_id[x] == x) {
        return x;
    }
    c->culture_id[x] = findParent(c, c->culture_id[x]);
    return c->culture_id[x];
}

int check_culture(struct context_t * c, int src, int dest) {
    if (c->area[dest] != 0) {
        int root_src = findParent(c, c->area[src]);
        int root_dest = findParent(c, c->area[dest]);
        if (root_dest != root_src) {
            if (root_dest < root_src) {
#ifdef DEBUG_OUTPUT
                printf("(%d,%d %d) (%d,%d %d) culture %d is combined\n", src & 0x7FF, src >> 11, root_src, dest & 0x7FF, dest >> 11, root_dest, root_src);
#endif
                c->culture_id[root_src] = root_dest;
                return 1;
            } else {
#ifdef DEBUG_OUTPUT
                printf("(%d,%d %d) (%d,%d %d) culture %d is combined\n", src & 0x7FF, src >> 11, root_src, dest & 0x7FF, dest >> 11, root_dest, root_dest);
#endif
                c->culture_id[root_dest] = root_src;
                return 1;
            }
        }
    }
    return 0;
}

int combine_culture(struct context_t * c, int x, int y)
{
    int count = 0;
    int src = (y << 11) | x;
    if (x > 0) {
        if (check_culture(c, src, src - 1)) {
            count++;
        }
    }
    if (x < c->n - 1) {
        if (check_culture(c, src, src + 1)) {
            count++;
        }
    }
    if (y > 0) {
        if (check_culture(c, src, src - 2048)) {
            count++;
        }
    }
    if (y < c->n - 1) {
        if (check_culture(c, src, src + 2048)) {
            count++;
        }
    }

    return count;
}

int fill_culture(struct context_t * c, int src, int dest) {
    struct stage_t * next = &c->stages[(c->turn + 1) % 2];

    if (c->area[dest] == 0) {
        c->area[dest] = c->area[src];
        next->edge_list[next->edge_count++] = dest;
    }
    return 0;
}

void fill_around(struct context_t * c, int x, int y)
{
    int src = (y << 11) | x;
    if (x > 0) {
        fill_culture(c, src, src - 1);
    }
    if (x < c->n - 1) {
        fill_culture(c, src, src + 1);
    }
    if (y > 0) {
        fill_culture(c, src, src - 2048);
    }
    if (y < c->n - 1) {
        fill_culture(c, src, src + 2048);
    }
}

int solve(struct context_t * c)
{
    while (c->k > 1) {
        int index = c->turn & 0x01;

        for (int j = 0; j < c->stages[index].edge_count; j++) {
            c->k -= combine_culture(c, c->stages[index].edge_list[j] & 0x7FF, c->stages[index].edge_list[j] >> 11);
        }

        if (c->k == 1) {
            break;
        }

        for (int j = 0; j < c->stages[index].edge_count; j++) {
            fill_around(c, c->stages[index].edge_list[j] & 0x7FF, c->stages[index].edge_list[j] >> 11);
        }
        c->stages[index].edge_count = 0;
        c->turn++;
    }
    return c->turn;
}

int main()
{
    int x;
    int y;

    memset(&context, 0, sizeof(context));

    scanf("%d %d", &context.n, &context.k);

    for (int i = 1; i <= context.k; i++) {
        int ix;
        int iy;
        int c;
        scanf("%d %d", &ix, &iy);
        x = ix - 1;
        y = iy - 1;
        c = (y << 11) | x;

        context.culture_id[i] = i;
        if (context.area[c] != 0) {
            context.k--;
        }
        context.area[c] = i;
        context.stages[0].edge_list[context.stages[0].edge_count++] = c;
    }

    printf("%d\n", solve(&context));
    return 0;
}
