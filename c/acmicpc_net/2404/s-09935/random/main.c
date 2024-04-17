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
    int N;
    int M;
    int n;
    int m;

    srand(time(NULL));
    N = get_rand(50, 10000);
    M = get_rand(1, 10);

    for (int n = 0; n < N; n++) {
        printf("%c", get_rand(0, 9) + 'a');
    }
    printf("\n");
    for (int m = 0; m < M; m++) {
        printf("%c", get_rand(0, 9) + 'a');
    }
    printf("\n");
    return 0;
}
