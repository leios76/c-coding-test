#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int c;
    int n;
    int k;

    uint32_t score[2];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        memset(score, 0, sizeof(score));
        for (int m = 0; m < 2; m++) {
            scanf("%d", &c);
            for (int j = 0; j < c; j++) {
                scanf("%d", &k);
                score[m] += (1 << ((k-1)*8));
            }
        }
        if (score[0] > score[1]) {
            printf("A\n");
        } else if (score[0] < score[1]) {
            printf("B\n");
        } else {
            printf("D\n");
        }
    }
    printf("\n");
    return 0;
}
