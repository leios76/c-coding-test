#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

struct site_t {
    uint64_t hash;
    char url[21];
    char password[21];
};
struct context_t {
    int n;
    int m;
    struct site_t sites[100000];
    char q[100000][21];
};
struct context_t context;


struct site_t sort_buffer[100000];
void merge_sort(struct site_t arr[], int left, int right) {
	if (left < right) {
		int mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

        int left_index = left;
        int right_index = mid + 1;
        int index = left;
        while (index <= mid && right_index <= right) {
            if (arr[index].hash <= arr[right_index].hash) {
                memcpy(&sort_buffer[left_index++], &arr[index++], sizeof(struct site_t));
            } else {
                memcpy(&sort_buffer[left_index++], &arr[right_index++], sizeof(struct site_t));
            }
        }
        memcpy(&sort_buffer[left_index], &arr[index], sizeof(struct site_t) * (mid - index + 1));
        memcpy(&sort_buffer[left_index + (mid - index + 1)], &arr[right_index], sizeof(struct site_t) * (right - right_index + 1));
        memcpy(&arr[left], &sort_buffer[left], sizeof(struct site_t) * (right - left + 1));
	}
}

uint64_t hash(char url[21])
{
    int result = 0;
    uint64_t hash = 0;
    uint64_t hash_sum = 0;
    uint64_t salt = 2305843009213693951ULL;
    int multi = 59;

    for (int l = 0; l < strlen(url); l++) {
        char ch = url[l];

        if ('a' <= ch && ch <= 'z') {
            hash = ch - 'a' + 1;
        }
        if ('A' <= ch && ch <= 'Z') {
            hash = ch - 'A' + 27;
        }
        if (ch == '.') {
            hash = 53;
        }
        if (ch == '-') {
            hash = 54;
        }
        for (int i = 0; i < l; i++) {
            hash = hash * multi;
            while (hash > salt) {
                hash -= salt;
            }
        }
        hash_sum += hash;
        while (hash_sum > salt) {
            hash_sum -= salt;
        }
    }
    return hash_sum;
}

int binary_search(uint64_t number, struct site_t arr[], int left, int right)
{
    int s = 0;
    int e = right;

    while (s <= e) {
        int d = (e + s) / 2;
        if (number == arr[d].hash) {
            return d;
        }


        if (number < arr[d].hash) {
            e = d - 1;
        } else {
            s = d + 1;
        }
    }
    return -1;
}


void solve(struct context_t * ctx)
{
    int result = 0;

    merge_sort(ctx->sites, 0, ctx->n - 1);

    for (int m = 0; m < ctx->m; m++) {
        uint64_t h = hash(ctx->q[m]);
        int i = binary_search(h, ctx->sites, 0, ctx->n - 1);
        printf("%s\n", ctx->sites[i].password);
    }
}

void init_data(struct context_t * ctx)
{
    memset(ctx, 0, sizeof(struct context_t));
    scanf("%d", &ctx->n);
    scanf("%d", &ctx->m);
    for (int n = 0; n < ctx->n; n++) {
        scanf("%s%s", ctx->sites[n].url, ctx->sites[n].password);
        ctx->sites[n].hash = hash(ctx->sites[n].url);
    }
    for (int m = 0; m < ctx->m; m++) {
        scanf("%s", ctx->q[m]);
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
