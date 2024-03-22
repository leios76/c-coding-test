#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 50;
int max_k = 5;

int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main()
{
    int n;
    int k;
    int ix;
    int iy;

    srand(time(NULL));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%d", get_rand(0, 1));
        }
        printf("\n");
    }

    k = get_rand(1, 5);
    printf("%d\n", k);

    for (int i = 1; i <= k; i++) {
        printf("%d %d\n", get_rand(1, 4), get_rand(0, 1) ? 1:-1);
    }
    return 0;
}
