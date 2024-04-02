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
    uint64_t meeting[100000];
};
struct context_t context;

uint64_t sort_buffer[100000];
void merge_sort(uint64_t arr[], int left, int right)
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
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(uint64_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(uint64_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(uint64_t) * (right - left + 1));
    }
}

int binary_search(int number, uint64_t arr[], int left, int right)
{
    int s = 0;
    int e = right;
    int d = -1;

    while (s <= e) {
        d = (e + s) / 2;
        if (number == (arr[d] >> 32)) {
            return d;
        }

        if (number < (arr[d] >> 32)) {
            e = d - 1;
        } else {
            s = d + 1;
        }
    }
    return d;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    uint64_t end_time = 0;
    merge_sort(ctx->meeting, 0, ctx->n - 1);
    for (int n = 0; n < ctx->n; n++) {
        if (end_time <= (ctx->meeting[n] & 0xFFFFFFFF)) {
            end_time = ctx->meeting[n] >> 32;
            debug("[%d] %lu %lu (%d)\n", n, ctx->meeting[n] & 0xFFFFFFFF, ctx->meeting[n] >> 32, end_time);
            result++;
        }
    }
    printf("%d\n", result);
}

void init_data(struct context_t * ctx)
{
    uint64_t s;
    uint64_t e;
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%lu%lu", &s, &e);
        ctx->meeting[n] = (e << 32) | s;
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
