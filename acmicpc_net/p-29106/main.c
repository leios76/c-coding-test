#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define CLUSTER_SIZE 16
#define CLUSTER_COUNT ((1000 * 1000 * 1024 + (1 << CLUSTER_SIZE) - 1) / (1 << CLUSTER_SIZE))

// #define RANDOM_RUN

#ifdef DEBUG_RUN
int debug_n = 7;
int debug_k = 3;
int debug_pool[] = {8, 8, 9, 13, 1, 5, 10};

#ifdef RANDOM_RUN
int debug_max_number = 1000 * 1000 * 1000 + 1;
#endif
#endif

int numbers[100 * 1024];
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))

int partition(int arr[], int left, int right)
{
    int pivot, temp;
    int low, high;

    low = left;
    high = right + 1;
    pivot = arr[left];

    do
    {
        do
        {
            low++;
        } while (low <= right && arr[low] < pivot);

        do
        {
            high--;
        } while (high >= left && arr[high] > pivot);

        if (low < high)
        {
            temp = arr[low];
            arr[low] = arr[high];
            arr[high] = temp;
        }
    } while (low < high);

    temp = arr[left];
    arr[left] = arr[high];
    arr[high] = temp;

    return high;
}

void quick_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int pivot = partition(arr, left, right);

        quick_sort(arr, left, pivot - 1);
        quick_sort(arr, pivot + 1, right);
    }
}

int main(int q, char **x)
{
    int n, k, v;
    int curr_index;

#ifdef DEBUG_RUN
#ifdef RANDOM_RUN
    srand(time(NULL));
#endif
#endif

#ifdef DEBUG_RUN
    n = debug_n;
    k = debug_k;
#else
    scanf("%d %d", &n, &k);
#endif
    int min = 1000000001;
    int min_index = 0;
    for (int i = 0; i < n; i++)
    {
#ifdef DEBUG_RUN
#ifdef RANDOM_RUN
        numbers[i] = rand() % debug_max_number;
#else
        numbers[i] = debug_pool[i];
#endif
#else
        scanf("%d", &numbers[i]);
#endif
    }

    quick_sort(numbers, 0, n - 1);

    for (int i = 0; i < n - k + 1; i++)
    {
        if (min > numbers[i + k - 1] - numbers[i])
        {
            min = numbers[i + k - 1] - numbers[i];
            min_index = i;
        }
    }
    for (int i = 0; i < k; i++)
    {
        printf("%d ", numbers[i + min_index]);
    }
    printf("\n");
    return 0;
}