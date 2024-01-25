#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int min_r = 999;
int min_c = 998;

int max_r = 999;
int max_c = 998;

int min_wall_count = 495 * 1000;
int min_fire_count = 1;

int max_wall_count = 498 * 1000;
int max_fire_count = 1;

int area[1000][1000];


// r 999 c998
// target: r0, c0
// fire: r500, c498
//
int main()
{
    int r;
    int c;
    int t;
    int x;
    int y;
    int wall_count;
    int fire_count;
    memset(area, 0, sizeof(area));

    srand(time(NULL));
    r = (rand() % (max_r - min_r + 1)) + min_r;
    c = (rand() % (max_c - min_c + 1)) + min_c;

    printf("%d %d\n", r, c);

#if 0
    x = rand() % c;
    y = rand() % r;
    area[y][x] = 3;

    fire_count = (rand() % (max_fire_count - min_fire_count + 1)) + min_fire_count;
    for (int i = 0; i < fire_count; i++) {
        while (1) {
            x = rand() % c;
            y = rand() % r;
            if (area[y][x] == 0) {
                area[y][x] = 2;
                break;
            }
        }
    }
#else
    area[0][0] = 3;
    area[500][498] = 2;
#endif

    wall_count = (rand() % (max_wall_count - min_wall_count + 1)) + min_wall_count;
    for (int i = 0; i < wall_count; i++) {
        while (1) {
            x = rand() % c;
            y = rand() % r;
            if (area[y][x] == 0) {
                area[y][x] = 1;
                break;
            }
        }
    }
    for (int j = 0; j < r; j++) {
        for (int i = 0; i < c; i++) {
            switch (area[j][i]) {
            case 0:
                printf(".");
                break;
            case 1:
                printf("#");
                break;
            case 2:
                printf("@");
                break;
            case 3:
                printf("&");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
