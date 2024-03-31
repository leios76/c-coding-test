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
    int m;
    int n;

    srand(time(NULL));
    m = get_rand(1, 400);
    n = get_rand(1, 400);

    printf("1\n%d %d %d %d\n", m, n, get_rand(1, m), get_rand(1, n));
    return 0;
}
