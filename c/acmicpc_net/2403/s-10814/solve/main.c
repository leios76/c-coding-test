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
    int age[100000];
    char name[100000][101];
    int index[100000];
};
struct context_t context;

int sort_buffer[100000];
void merge_sort(struct context_t * ctx, int arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(ctx, arr, left, mid);
		merge_sort(ctx, arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (ctx->age[arr[index]] < ctx->age[arr[right_index]] || (ctx->age[arr[index]] == ctx->age[arr[right_index]] && index < right_index)) {
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

void solve(struct context_t * ctx)
{
    int result = 0;
    merge_sort(ctx, ctx->index, 0, ctx->n - 1);
    for (int n = 0; n < ctx->n; n++) {
        printf("%d %s\n", ctx->age[ctx->index[n]], ctx->name[ctx->index[n]]);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d%s", &ctx->age[n], ctx->name[n]);
        ctx->index[n] = n;
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
