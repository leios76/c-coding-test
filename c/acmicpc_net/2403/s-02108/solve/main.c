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
    int max;
    int min;
    int mid;
    int total;
    int n;
    int c[8001];
    int max_c_v[2];
    int v[500000];
};
struct context_t context;


int sort_buffer[500000];
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

void solve(struct context_t * ctx)
{
    int result = 0;

    merge_sort(ctx->v, 0, ctx->n - 1);

    if (ctx->total >= 0) {
        int avg = (ctx->total * 1.0 / ctx->n + 0.5);
        printf("%d\n", avg);
    } else {
        int avg = (ctx->total * 1.0 / ctx->n - 0.5);
        printf("%d\n", avg);
    }
    printf("%d\n", ctx->v[ctx->n/2]);
    printf("%d\n", (ctx->max_c_v[1] == -4001) ? ctx->max_c_v[0]:ctx->max_c_v[1]);
    printf("%d\n", ctx->v[ctx->n - 1] - ctx->v[0]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    int max = 0;
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->v[n]);
        ctx->total += ctx->v[n];
        ctx->c[ctx->v[n] + 4000]++;
        if (ctx->c[ctx->v[n] + 4000] > max) {
            max = ctx->c[ctx->v[n] + 4000];
            ctx->max_c_v[0] = ctx->v[n];
            ctx->max_c_v[1] = -4001;
        } else if (ctx->c[ctx->v[n] + 4000] == max) {
            if (ctx->max_c_v[1] == -4001) {
                if (ctx->max_c_v[0] > ctx->v[n]) {
                    ctx->max_c_v[1] = ctx->max_c_v[0];
                    ctx->max_c_v[0] = ctx->v[n];
                } else {
                    ctx->max_c_v[1] = ctx->v[n];
                }
            } else {
                if (ctx->max_c_v[0] > ctx->v[n]) {
                    ctx->max_c_v[1] = ctx->max_c_v[0];
                    ctx->max_c_v[0] = ctx->v[n];
                } else if (ctx->max_c_v[1] > ctx->v[n]) {
                    ctx->max_c_v[1] = ctx->v[n];
                }
            }
            debug("update max c %d %d\n", ctx->max_c_v[0], ctx->max_c_v[1]);
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
