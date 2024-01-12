#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int t;
    int x;
    int y;
    int n;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &x, &y, &n);
        if (abs(x) + abs(y) <= n && (n - abs(x) - abs(y)) % 2 == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}
