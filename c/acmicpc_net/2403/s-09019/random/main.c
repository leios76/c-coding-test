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
    printf("1\n");
    while (1) {
        int a = get_rand(1, 1000);
        int b = get_rand(1, 1000);
        if (a == b) {
            continue;
        }
        printf("%d %d\n", a, b);
        break;
    }
    return 0;
}
