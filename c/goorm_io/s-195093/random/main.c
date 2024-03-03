#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 16;

int main()
{
    int n;
    int t;

    srand(time(NULL));
    n = (rand() % max_n) + 1;

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        printf("%d ", rand() % 10);
    }
    printf("\n");
    return 0;
}
