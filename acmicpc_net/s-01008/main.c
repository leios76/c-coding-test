#include <stdio.h>

int main(int q, char ** x)
{
    int a, b;
    scanf("%d %d", &a, &b);

    printf("%.12f\n", (double)a / (double)b);
    return 0;
}