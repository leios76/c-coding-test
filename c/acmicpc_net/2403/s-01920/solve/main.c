#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef DEBUG_OUTPUT
#include <time.h>
#endif

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif


int sort_buffer[100000];
void merge_sort(int arr[], int left, int right)
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (arr[index] <= arr[right_index]) {
                sort_buffer[left_index++] = arr[index++];
            } else {
                sort_buffer[left_index++] = arr[right_index++];
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(int) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(int) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(int) * (right - left + 1));
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

    merge_sort(ctx->a, 0, ctx->n - 1);

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
                e = d - 1;
            } else {
                s = d + 1;
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

    int elapsed = 0;
#ifdef DEBUG_OUTPUT
    struct      timespec mytime;

    // 현재 시간을 얻어온다.
    clock_gettime(CLOCK_MONOTONIC, &mytime);
    elapsed = (mytime.tv_sec * 1000LL + mytime.tv_nsec / 1000LL / 1000LL);
#endif

    //scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        init_data(&context);
        solve(&context);
    }

#ifdef DEBUG_OUTPUT
    clock_gettime(CLOCK_MONOTONIC, &mytime);
    elapsed = (mytime.tv_sec * 1000LL + mytime.tv_nsec / 1000LL / 1000LL) - elapsed;
#endif
    return elapsed;
}
