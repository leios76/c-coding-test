#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int n;
    int m;
    int max_value[9];
    int cur_value[9];
    int inc_value[9];
    int k;

    memset(max_value, 0, sizeof(max_value));
    memset(cur_value, 0, sizeof(cur_value));
    memset(inc_value, 0, sizeof(inc_value));
    scanf("%d", &n);

    for (int i = n - 1; i >= 0; i--) {
        scanf("%d", &max_value[i]);
        max_value[i]++;
    }

    for (int i = n - 1; i >= 0; i--) {
        scanf("%d", &cur_value[i]);
    }
    scanf("%d", &k);

    for (int i = 0; i < n; i++) {
        int inc = 1;
        for (int j = 0; j < i ; j++) {
            inc = inc * (max_value[j]);
        }
        inc_value[i] = inc;
    }

    while (k > 0) {
        for (int i = n - 1; i >= 0; i--) {
            if (k >= inc_value[i]) {
                k -= inc_value[i];
                cur_value[i]++;
                for (int j = i; j < n; j++) {
                    if (cur_value[j] >= max_value[j]) {
                        cur_value[j] -= max_value[j];
                        cur_value[j + 1]++;
                    }
                }
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        printf("%d", cur_value[i]);
    }
    printf("\n");

    return 0;
}
