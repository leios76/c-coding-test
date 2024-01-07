#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint64_t bitmap[4][128*128/16];

uint8_t region[4][128*128];
uint8_t region_count[4];

void mark_region(int color, int x, int y)
{
    int around_c[4] = {-1, -128, 1, 128};
    int around_x[4] = {-1, 0, 1, 0};
    int around_y[4] = {0, -1, 0, 1};
    int c = y * 128 + x;

    int candidate_x[4] = {0, 0, 0, 0};
    int candidate_y[4] = {0, 0, 0, 0};

    if (bitmap[color][c/64] & (1ULL << (c%64)) && region[color][c] == 0) {
        for (int a = 0; a < 4; a++) {
            if (bitmap[color][(c + around_c[a])/64] & (1ULL << ((c + around_c[a])%64))) {
                if (region[color][c + around_c[a]] > 0) {
                    region[color][c] = region[color][c + around_c[a]];
                } else {
                    candidate_x[a] = x + around_x[a];
                    candidate_y[a] = y + around_y[a];
                }
            }
        }

        if (region[color][c] == 0) {
            region_count[color]++;
            region[color][c] = region_count[color];
        }

        for (int a = 0; a < 4; a++) {
            if (candidate_x[a] > 0 && candidate_y[a] > 0) {
                mark_region(color, candidate_x[a], candidate_y[a]);
            }
        }
        return;
    }
}

int main(int q, char ** x) {
    char line[101];
    int size;

    memset(bitmap, 0, sizeof(bitmap));
    scanf("%d", &size);

    for (int y = 1; y <= size; y++) {
        scanf("%s", line);

        for (int x = 1; x <= size; x++) {
            switch (line[x - 1]) {
                case 'R':
                    bitmap[0][(y * 128 + x) / 64] |= (1ULL << ((y*128+x) % 64));
                    bitmap[3][(y * 128 + x) / 64] |= (1ULL << ((y*128+x) % 64));
                    break;
                case 'G':
                    bitmap[1][(y * 128 + x) / 64] |= (1ULL << ((y*128+x) % 64));
                    bitmap[3][(y * 128 + x) / 64] |= (1ULL << ((y*128+x) % 64));
                    break;
                case 'B':
                    bitmap[2][(y * 128 + x) / 64] |= (1ULL << ((y*128+x) % 64));
                    break;
            }
        }
    }

    memset(region, 0, sizeof(region));
    memset(region_count, 0, sizeof(region_count));
    for (int y = 1; y <= size; y++) {
        for (int x = 1; x <= size; x++) {
            for (int c = 0; c < 4; c++) {
                mark_region(c, x, y);
            }
        }
    }

    printf("%d %d\n", region_count[0] + region_count[1] + region_count[2], region_count[2] + region_count[3]);
    return 0;
}