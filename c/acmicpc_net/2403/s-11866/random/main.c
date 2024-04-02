#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 1000;
int min_n = 1;
int max_k = 1000;
int min_k = 1;

int main()
{
    int n;
    int k;

    srand(time(NULL));
    n = rand() % (max_n - min_n + 1) + min_n;
    k = rand() % (n - min_k + 1) + min_k;

    printf("%d %d\n", n, k);
    return 0;
}
