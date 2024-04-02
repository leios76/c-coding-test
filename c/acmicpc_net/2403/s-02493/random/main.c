#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 500000;
int min_n = 1;
int max_height = 100000000;
int min_height = 1;

int main()
{
    int n;
    int h;

    srand(time(NULL));
    n = (rand() % (max_n - min_n + 1)) + min_n;

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        h = (rand() % (max_height - min_height + 1)) + min_height;
        printf("%d ", h);
    }
    printf("\n");
    return 0;
}
