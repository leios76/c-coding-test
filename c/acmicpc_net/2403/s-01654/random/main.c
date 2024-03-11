#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 1000000;
int min_n = 1;
int max_k = 10000;
int min_k = 1;

int main()
{
    int n;
    int k;
    int l;

    srand(time(NULL));
    k = rand() % (max_k - min_k + 1) + min_k;
    n = rand() % (max_n - k + 1) + k;

    printf("%d %d\n", k, n);

    for (int i = 0; i < k; i++) {
        l = rand() % 0x7FFFFFFF + 1;
        printf("%d\n", l);
    }
    return 0;
}
