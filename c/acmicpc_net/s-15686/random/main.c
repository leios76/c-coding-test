#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 50;
int max_m = 13;

int min_n = 2;
int min_m = 1;

int max_house_count;
int min_house_count = 1;

int max_shop_count = 13;
int min_shop_count = 1;

int map[50][50];

int main()
{
    int n;
    int m;
    int house_count;
    int shop_count;

    srand(time(NULL));
    n = (rand() % (max_n - min_n + 1)) + min_n;
    m = (rand() % (max_m - min_m + 1)) + min_m;
    printf("%d %d\n", n, m);

    max_house_count = n * 2;

    house_count = (rand() % (max_house_count - min_house_count + 1)) + min_house_count;
    shop_count = (rand() % (max_shop_count - m + 1)) + m;
    memset(map, 0, sizeof(map));

    while (house_count > 0) {
        int house_r = rand() % n;
        int house_c = rand() % n;

        if (map[house_r][house_c] != 1) {
            map[house_r][house_c] = 1;
            house_count--;
        }
    }

    while (shop_count > 0) {
        int shop_r = rand() % n;
        int shop_c = rand() % n;

        if (map[shop_r][shop_c] != 1) {
            map[shop_r][shop_c] = 2;
            shop_count--;
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            printf("%d ", map[r][c]);
        }
        printf("\n");
    }

    return 0;
}
