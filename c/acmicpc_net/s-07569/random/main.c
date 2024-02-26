#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 50;
int max_k = 5;

int main()
{
    int n;
    int k;
    int ix;
    int iy;

    srand(time(NULL));
    n = rand() % (max_n - 1) + 2;
    k = rand() % max_k + 1;

    printf("%d %d\n", n, k);

    for (int i = 1; i <= k; i++) {
        ix = rand() % n + 1;
        iy = rand() % n + 1;
        printf("%d %d\n", ix, iy);
    }
    return 0;
}
