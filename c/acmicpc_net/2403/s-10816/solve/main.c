#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif


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

struct context_t {
    int n;
    int ni[500000];
    int nc[500000];
    int m;
    int mi[500000];
};
struct context_t context;

int binary_search(int number, int arr[], int left, int right)
{
    int s = 0;
    int e = right;

    while (s <= e) {
        int d = (e + s) / 2;
        if (number == arr[d]) {
            return d;
        }


        if (number < arr[d]) {
            e = d -1;
        } else {
            s = d +1;
        }
    }
    return -1;
}

void solve(struct context_t * ctx)
{
    merge_sort(ctx->ni, 0, ctx->n - 1);
    int v = -10000001;
    int c = 0;
    int index = 0;
    for (int n = 0; n < ctx->n; n++) {
        if (v != ctx->ni[n]) {
            for (int i = index; i < n; i++) {
                ctx->nc[i] = c;
            }
            c = 0;
            index = n;
            v = ctx->ni[n];
        }
        c++;
    }
    for (int i = index; i < ctx->n; i++) {
        ctx->nc[i] = c;
    }

    for (int m = 0; m < ctx->m; m++) {
        int index = binary_search(ctx->mi[m], ctx->ni, 0, ctx->n - 1);
        if (index > -1) {
            printf("%d ", ctx->nc[index]);
        } else {
            printf("0 ");
        }
    }
    printf("\n");
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%d", &ctx->ni[n]);
    }
    scanf("%d", &ctx->m);
    for (int m = 0; m < ctx->m; m++) {
        scanf("%d", &ctx->mi[m]);
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
