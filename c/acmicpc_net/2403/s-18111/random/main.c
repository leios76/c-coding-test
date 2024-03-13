#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 500;
int min_n = 1;
int max_m = 500;
int min_m = 1;

int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main()
{
    int n;
    int m;
    int b;

    srand(time(NULL));
    n = get_rand(1, 500);
    m = get_rand(1, 500);
    b = get_rand(0, 64000000);

    printf("%d %d %d\n", n, m, b);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", get_rand(0, 256));
        }
        printf("\n");
    }
    return 0;
}
