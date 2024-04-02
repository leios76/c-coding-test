#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct name_t {
    char name[24];
};

struct context_t {
    int n;
    int m;
    struct name_t name_n[500000];
    struct name_t name_m[500000];

    int same_n[500000];
};
struct context_t context;


struct name_t sort_buffer[500000];
void merge_sort(struct name_t arr[], int left, int right)
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
                memcpy(&sort_buffer[left_index++], &arr[index++], sizeof(struct name_t));
            } else {
                memcpy(&sort_buffer[left_index++], &arr[right_index++], sizeof(struct name_t));
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(struct name_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(struct name_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(struct name_t) * (right - left + 1));
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;
    merge_sort(ctx->name_n, 0, ctx->n - 1);
    merge_sort(ctx->name_m, 0, ctx->m - 1);

    int n = 0;
    int m = 0;
    while (n < ctx->n && m < ctx->m) {
        int c = strcmp(ctx->name_n[n].name, ctx->name_m[m].name);
        if (c == 0) {
            ctx->same_n[result++] = n;
            if (n < ctx->n) {
                n++;
            }
            if (m < ctx->m) {
                m++;
            }
        } else if (c < 0) {
            if (n < ctx->n) {
                n++;
            }
        } else if (c > 0) {
            if (m < ctx->m) {
                m++;
            }
        }
    }
    printf("%d\n", result);
    for (int i = 0; i < result; i++) {
        printf("%s\n", ctx->name_n[ctx->same_n[i]].name);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s", ctx->name_n[n].name);
    }
    for (int m = 0; m < ctx->m; m++) {
        scanf("%s", ctx->name_m[m].name);
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
