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
    uint64_t coords[100000];
};
struct context_t context;

uint64_t sort_buffer[100000];
void merge_sort(uint64_t arr[], int left, int right) {
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
            }
            else {
                sort_buffer[left_index++] = arr[right_index++];
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(uint64_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(uint64_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(uint64_t) * (right - left + 1));
	}
}

void solve(struct context_t * ctx)
{
    int result = 0;

    merge_sort(ctx->coords, 0, ctx->n - 1);
    for (int n = 0; n < ctx->n; n++) {
        int x;
        int y;
        x = (ctx->coords[n] & 0xFFFFFFFF);
        y = (ctx->coords[n] >> 32);
        printf("%d %d\n", x - 100000, y - 100000);
    }
}

void init_data(struct context_t * ctx)
{
    uint32_t x;
    uint32_t y;
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d%d", &x, &y);
        ctx->coords[n] = ((uint64_t)(y + 100000) << 32) | (uint64_t)(x + 100000);
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
