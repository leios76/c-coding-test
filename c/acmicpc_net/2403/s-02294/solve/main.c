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
    int k;
    int value[100];
    int dp[100000];
};
struct context_t context;


int sort_buffer[100];
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

int get_dp(struct context_t * ctx, int sum)
{
    debug("get dp %d\n", sum);
    if (sum == ctx->k) {
        return 0;
    }
    if (sum > ctx->k) {
        return 10000000;
    }
    if (ctx->dp[sum] != -1) {
        return ctx->dp[sum];
    }

    int count = 0;
    int min_count = 0x7FFFFFFF;
    for (int n = 0; n < ctx->n; n++) {
        if (sum < ctx->k) {
            count = 1 + get_dp(ctx, sum + ctx->value[n]);
            if (min_count > count) {
                debug("%d: min %d\n", sum, count);
                min_count = count;
            }
        }
    }
    ctx->dp[sum] = min_count;
    return ctx->dp[sum];
}

void solve(struct context_t * ctx)
{
    int result = 0;
    merge_sort(ctx->value, 0, ctx->n - 1);
    for (int n = 0; n < ctx->n; n++) {
        debug("v: %d\n", ctx->value[n]);
    }
    get_dp(ctx, 0);
    printf("%d\n", (ctx->dp[0] >= 10000000) ? -1:ctx->dp[0]);
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    memset(ctx->dp, -1, sizeof(ctx->dp));
    scanf("%d%d", &ctx->n, &ctx->k);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->value[n]);
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
