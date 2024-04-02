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
    srand(time(NULL));
    printf("%d\n", get_rand(1, 50000));
    return 0;
}
