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
    int t;

    srand(time(NULL));
    t = 100; //get_rand(1, 100);
    for (int j = 0; j < t; j++) {
        n = 30; // get_rand(1, 30);

        printf("%d\n", n);

        for (int i = 1; i <= n; i++) {
            printf("%c%c%c %c%c%c\n", get_rand(0, 25) + 'a', get_rand(0, 25) + 'a', get_rand(0, 25) + 'a',
            get_rand(0, 25) + 'a', get_rand(0, 25) + 'a', get_rand(0, 25) + 'a');
        }
    }
    return 0;
}
