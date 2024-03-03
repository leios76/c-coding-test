#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 50;
int max_score = 10;

int main()
{
    int n;
    int d;
    int ix;
    int iy;

    srand(time(NULL));
    n = (rand() % max_n) + 1;

    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        d = (rand() % 4);
        switch (d) {
        case 0:
            printf("L");
            break;
        case 1:
            printf("R");
            break;
        case 2:
            printf("U");
            break;
        case 3:
            printf("D");
            break;
        }
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", (rand() % max_score) + 1);
    }
    printf("\n");
    return 0;
}
