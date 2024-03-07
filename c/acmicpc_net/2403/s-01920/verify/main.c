#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

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

struct context_t {
    int n;
    int a[100000];
    int m;
    int ma[1000000];
};

struct context_t context;

void solve(struct context_t * ctx)
{
    int result = 0;

    quick_sort(ctx->a, 0, ctx->n - 1);

    for (int m = 0; m < ctx->m; m++) {
        result = 0;
        int s = 0;
        int e = ctx->n - 1;

        while (s <= e) {
            int d = (e + s) / 2;

            //debug("s %d e %d d %d, %d vs %d\n", s, e, d, ctx->ma[m], ctx->a[d]);
            if (ctx->ma[m] == ctx->a[ d]) {
                result = 1;
                break;
            }

            if (ctx->ma[m] < ctx->a[ d]) {
                e = d -1;
            } else {
                s = d +1;
            }
        }
        printf("%d\n", result);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->a[n]);
    }
    scanf("%d", &ctx->m);
    for (int m = 0; m < ctx->m; m++) {
        scanf("%d", &ctx->ma[m]);
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
