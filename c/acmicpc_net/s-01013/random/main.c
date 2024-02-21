#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 200;

int main()
{
    int n;

    srand(time(NULL));
    printf("1\n");
    n = rand() % max_n + 1;

    for (int i = 1; i <= n; i++) {
        if (rand() % 2) {
            printf("0");
        } else {
            printf("1");
        }
    }
    printf("\n");
    return 0;
}
