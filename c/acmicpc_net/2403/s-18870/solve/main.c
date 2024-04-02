#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct entry_t {
    int i;
    int x;
    int z;
};

struct context_t {
    int n;
    struct entry_t x[1000001];
};
struct context_t context;

struct entry_t sort_buffer[1000001];
void merge_sort1(struct entry_t arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort1(arr, left, mid);
		merge_sort1(arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (arr[index].x <= arr[right_index].x) {
                sort_buffer[left_index].i = arr[index].i;
                sort_buffer[left_index++].x = arr[index++].x;
            }
            else {
                sort_buffer[left_index].i = arr[right_index].i;
                sort_buffer[left_index++].x = arr[right_index++].x;
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(struct entry_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(struct entry_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(struct entry_t) * (right - left + 1));
	}
}

void merge_sort2(struct entry_t arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort2(arr, left, mid);
		merge_sort2(arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (arr[index].i <= arr[right_index].i) {
                sort_buffer[left_index].i = arr[index].i;
                sort_buffer[left_index].z = arr[index].z;
                sort_buffer[left_index++].x = arr[index++].x;
            }
            else {
                sort_buffer[left_index].i = arr[right_index].i;
                sort_buffer[left_index].z = arr[right_index].z;
                sort_buffer[left_index++].x = arr[right_index++].x;
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(struct entry_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(struct entry_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(struct entry_t) * (right - left + 1));
	}
}

void solve(struct context_t * ctx)
{
    int result = 0;
    merge_sort1(ctx->x, 0, ctx->n - 1);

    for (int n = 0; n < ctx->n; n++) {
        ctx->x[n].z = result;
        if (ctx->x[n].x != ctx->x[n + 1].x) {
            result++;
        }
    }
    merge_sort2(ctx->x, 0, ctx->n - 1);
    for (int n = 0; n < ctx->n; n++) {
        printf("%d ", ctx->x[n].z);
    }
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->x[n].x);
        ctx->x[n].i = n;
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
