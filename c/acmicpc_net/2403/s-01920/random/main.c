#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 100000;
int min_n = 1;
int max_m = 100000;
int min_m = 1;

int main()
{
    int n;
    int m;

    int a;
    int seed;
    struct      timespec mytime;

    // 현재 시간을 얻어온다.
    clock_gettime(CLOCK_MONOTONIC, &mytime);
    seed = ( mytime.tv_sec * 1000LL + mytime.tv_nsec / 1000LL / 1000LL);

    srand(seed);
    n = rand() % (max_n - min_n + 1) + min_n;
    m = rand() % (max_m - min_m + 1) + min_m;

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        a = rand() % 0xFFFFFFFF;
        printf("%d ", a);
    }
    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        a = rand() % 0xFFFFFFFF;
        printf("%d ", a);
    }
    return 0;
}
