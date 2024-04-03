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
    int m;
    int dfs_v[9];
    int values[9];
    int v[9];
};
struct context_t context;

int sort_buffer[9];
void merge_sort(int arr[], int left, int right) {
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
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(int) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(int) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(int) * (right - left + 1));
	}
}

void dfs(struct context_t * ctx, int s, int depth)
{
    if (depth > ctx->m) {
        for (int m = 1; m <= ctx->m; m++) {
            printf("%d ", ctx->values[m]);
        }
        printf("\n");
        return;
    }
    for (int n = 0; n < ctx->n; n++) {
        if (ctx->values[depth - 1] <= n) {
            ctx->values[depth] = ctx->v[n];
            dfs(ctx, n, depth + 1);
        }
    }
}

void solve(struct context_t * ctx)
{
    int result = 0;
    merge_sort(ctx->v, 0, ctx->n - 1);
    dfs(ctx, 0, 1);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->v[n]);
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
