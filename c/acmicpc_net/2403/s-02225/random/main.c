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

    srand(time(NULL));
    n = get_rand(1, 200);
    k = get_rand(1, 200);

    printf("%d %d\n", n, k);
    return 0;
}
