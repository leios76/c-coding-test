#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int n;
    int m;

    scanf("%d %d", &n, &m);
    printf("%.2f\n", (int)((700 * n) / (n + m)) / 100.0);

    return 0;
}
