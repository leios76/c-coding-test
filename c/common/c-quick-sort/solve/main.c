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
    int n;
    int d;
    int pos[100000];
};
struct context_t context;

int partition(int arr[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = arr[left];

    do {
        do {
            low++;
        } while (low <= right && arr[low] < pivot);

        do {
            high--;
        } while (high >= left && arr[high] > pivot);

        if (low < high) {
            temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
        }
    } while (low < high);

    temp = arr[left];
    arr[left] = arr[high];
    arr[high] = temp;

    return high;
}

void quick_sort(int arr[], int left, int right)
{
    if (left < right) {
        int pivot = partition(arr, left, right);

        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    }
}

int solve(struct context_t * ctx)
{
    int start_index = 0;
    int max_index = 0;
    int curr_group = 0;
    int max_group = 0;
    for (int i = 0; i < ctx->n; i++) {
        while ((ctx->pos[i] - ctx->pos[start_index]) > ctx->d) {
            start_index++;
        }
        if (start_index == ctx->n - 1) {
            break;
        }
        curr_group = i - start_index + 1;
        debug("[%d] start index: %d, group: %d, distance: %d - %d = %d\n", i, start_index, curr_group, ctx->pos[i], ctx->pos[start_index], ctx->pos[i] - ctx->pos[start_index]);
        if (max_group < curr_group) {
            max_group = curr_group;
            max_index = start_index;
            debug("new max index: (%d)%d\n", max_index, max_group);
        }
    }

    return ctx->n - max_group;
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));

    scanf("%d %d", &ctx->n, &ctx->d);

    for (int i = 0; i < ctx->n; i++) {
        scanf("%d", &ctx->pos[i]);
    }
    quick_sort(ctx->pos, 0, ctx->n - 1);
}

int main()
{
    init_data(&context);
    printf("%d\n", solve(&context));

    return 0;
}
