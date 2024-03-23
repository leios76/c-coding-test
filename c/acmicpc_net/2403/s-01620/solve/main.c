#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct monster_t {
    char name[21];
    int number;
};

struct context_t {
    int n;
    int m;
    struct monster_t name_list[100000];
    struct monster_t number_list[100000];
    struct monster_t q[100000];
};
struct context_t context;


struct monster_t sort_buffer[100000];
void merge_sort(struct monster_t arr[], int left, int right)
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (strcmp(arr[index].name, arr[right_index].name) <= 0) {
                memcpy(&sort_buffer[left_index++], &arr[index++], sizeof(struct monster_t));
            } else {
                memcpy(&sort_buffer[left_index++], &arr[right_index++], sizeof(struct monster_t));
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(struct monster_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(struct monster_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(struct monster_t) * (right - left + 1));
    }
}


int binary_search(char * name, struct monster_t arr[], int left, int right)
{
    int s = 0;
    int e = right;

    while (s <= e) {
        int d = (e + s) / 2;
        int c = strcmp(name, arr[d].name);
        if (c == 0) {
            return d;
        }


        if (c < 0) {
            e = d - 1;
        } else {
            s = d + 1;
        }
    }
    return -1;
}

void solve(struct context_t * ctx)
{
    merge_sort(ctx->name_list, 0, ctx->n - 1);

    for (int m = 0; m < ctx->m; m++) {
        if (ctx->q[m].number == 0) {
            int d = binary_search(ctx->q[m].name, ctx->name_list, 0, ctx->n - 1);
            printf("%d\n", ctx->name_list[d].number);
        } else {
            printf("%s\n", ctx->number_list[ ctx->q[m].number - 1].name);
        }
    }
}

void init_data(struct context_t * ctx)
{
    char line[21];
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        ctx->name_list[n].number = n + 1;
        scanf("%s", ctx->name_list[n].name);
    }
    memcpy(ctx->number_list, ctx->name_list, sizeof(struct monster_t) * ctx->n);
    for (int m = 0; m < ctx->m; m++) {
        scanf("%s", line);
        ctx->q[m].number = atoi(line);
        if (ctx->q[m].number == 0) {
            strcpy(ctx->q[m].name, line);
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
