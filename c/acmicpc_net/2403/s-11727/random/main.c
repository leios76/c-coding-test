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
    srand(time(NULL));
    printf("%d\n", get_rand(1, 1000));
    return 0;
}
