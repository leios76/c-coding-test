#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 100000;
int min_n = 1;

uint32_t bitmap[100031 / 32];

int main()
{
    int n;

    memset(bitmap, 0, sizeof(bitmap));
    srand(time(NULL));
    n = rand() % (max_n - min_n) + min_n;

    printf("%d\n", n);

    for (int i = 0; i < n;) {
        int v = rand() % n + 1;
        if ((bitmap[v / 32] & (1 << v)) != 0) {
            continue;
        }
        printf("%d\n", v);
        i++;
        bitmap[v / 32] |= (1 << v);
    }
    return 0;
}
