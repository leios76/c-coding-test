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
    int h[1000000];
    uint64_t s[1000000];
};
struct context_t context;


int sort_buffer[1000000];
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

int binary_search(int number, int arr[], int left, int right)
{
    int s = 0;
    int e = right;
    int d = 0;

    while (s <= e) {
        d = (e + s) / 2;
        if (number == arr[d]) {
            return d;
        }


        if (number < arr[d]) {
            e = d -1;
        } else {
            s = d +1;
        }
    }
    return d;
}

void solve(struct context_t * ctx)
{
    int result = 0;
    uint64_t cut_line = 0;
    int min_index = 0;
    uint64_t sum;
    int count;
    merge_sort(ctx->h, 0, ctx->n - 1);
    ctx->s[0] = ctx->h[0];
    for (int n = 1; n < ctx->n; n++) {
        ctx->s[n] = ctx->s[n - 1] + ctx->h[n];
    }

    while (1) {
        if (min_index > 0) {
            sum = (ctx->s[ctx->n - 1] - ctx->s[min_index - 1]);
        } else {
            sum = ctx->s[ctx->n - 1];
        }
        count = ctx->n - 1 - min_index + 1;
        sum -= cut_line * count;
        if ((sum - ctx->m) / count == 0 || sum < ctx->m) {
            break;
        }
        cut_line += (sum - ctx->m) / count;
        int index = binary_search(cut_line, ctx->h, min_index, ctx->n - 1);
        for (int n = index; n < ctx->n; n++) {
            if (cut_line < ctx->h[n]) {
                min_index = n;
                break;
            }
        }
    }
    printf("%d\n", cut_line);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->h[n]);
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
