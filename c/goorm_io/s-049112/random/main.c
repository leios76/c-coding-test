#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 100000;
int max_p = 1001;

int main()
{
    int n;
    int k;

    srand(time(NULL));
    n = (rand() % max_n) + 1;

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        int p = rand() % max_p;
        printf("%d ", p);
    }
    printf("\n");
    return 0;
}
