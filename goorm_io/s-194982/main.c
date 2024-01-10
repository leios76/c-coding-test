#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int n;
    int m;
    int k[1001];
    int r[1001];
    int s;
    int e;

    memset(k, 0, sizeof(k));
    memset(r, 0, sizeof(r));

    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &s, &e);
        for (int j = s; j <= e; j++) {
            r[j]++;
        }
        if (((i + 1) % 3) == 0) {
            for (int j = 1; j <= n; j++) {
                if (r[j] > 0) {
                    r[j]--;
                }
                k[j] += r[j];
                r[j] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", k[i] + r[i]);
    }
    printf("\n");

    return 0;
}
