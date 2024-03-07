#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 1000000;
int min_n = 1;

int max_v = 1000000;
int min_v = 1;

int main()
{
    int n;
    int v;

    srand(time(NULL));
    n = rand() % (max_n - min_n + 1) + min_n;

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        v = rand() % (max_v - min_v + 1) + min_v;
        printf("%d\n", v);
    }
    return 0;
}
