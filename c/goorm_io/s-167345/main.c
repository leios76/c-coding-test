#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

int area[40][40];
int diff[40][40];

int get_around(int x, int y, int n)
{
    int value = 0;
    if (x > 0 && area[x - 1][y] == 0) {
        value++;
    }
    if (y > 0 && area[x][y - 1] == 0) {
        value++;
    }
    if (x < n - 1 && area[x + 1][y] == 0) {
        value++;
    }
    if (y < n - 1 && area[x][y + 1] == 0) {
        value++;
    }

    return value;
}

int process_value(int n)
{
}

int main()
{
    int n;
    int t;
    int done;
    int sum;

    memset(area, 0, sizeof(area));
    scanf("%d", &n);

    sum = 0;
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            scanf("%d", &area[x][y]);
            sum += area[x][y];
        }
    }

    t = 0;
    while (sum > 0) {
        t++;
        memset(diff, 0, sizeof(diff));
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                diff[x][y] = get_around(x, y, n);
            }
        }
#ifdef DEBUG_OUTPUT
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                printf("%d(%d) ", area[x][y], diff[x][y]);
            }
            printf("\n");
        }
        printf("\n");
#endif
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if (area[x][y] > 0) {
                    sum -= area[x][y];
                    area[x][y] -= (diff[x][y]);
                    if (area[x][y] < 0) {
                        area[x][y] = 0;
                    }
                    sum += area[x][y];
                }
            }
        }
    }

    printf("%d\n", t);
    return 0;
}