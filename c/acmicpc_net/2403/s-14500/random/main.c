#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main()
{
    int n;
    int m;

    srand(time(NULL));
    n = get_rand(4, 100);
    m = get_rand(4, 100);

    printf("%d %d\n", n, m);

    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            printf("%d ", get_rand(1, 500));
        }
        printf("\n");
    }
    return 0;
}
