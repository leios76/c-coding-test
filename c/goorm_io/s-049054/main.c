#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int n;
    int v;
    int s;
    scanf("%d", &n);

    if (n == 0) {
        printf("1\n");
        return 0;
    }

    v = 1;
    for (int i = 1; i <= n; i++) {
        v = v * i;
        if (v % 9 == 0) {
            printf("9\n");
            return 0;
        }
    }

    do {
        s = 0;
        while (v > 0) {
            s += v % 10;
            v = v / 10;
        }
        v = s;
    } while (s > 10);

    printf("%d\n", s);
    return 0;
}