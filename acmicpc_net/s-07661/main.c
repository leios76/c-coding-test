#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int sx[1000];
int sy[1000];

uint64_t mm[1024 * 1024 / 64];
int al(int m, int n, int s, int r, int c)
{
    int b = 0;
    uint64_t cl[1024 / 64];
    uint64_t dl[1024 / 64];

    memset(mm, 0, sizeof(mm));
    memset(dl, 0, sizeof(dl));
    for (int x = 0; x < n; x++) {
        dl[x / 64] |= (1ULL << (x % 64));
    }

    for (b = 0; b < 1000; b++) {
        int d1 = 1;
        int d2 = 1;

        for (int i = 0; i < s; i++) {
            memset(cl, 0, sizeof(cl));
            for (int x = sx[i] - b; x <= sx[i] + b; x++) {
                if (0 <= x && x < n) {
                    cl[x / 64] |= (1ULL << (x % 64));
                }
            }

            for (int y = sy[i] - b; y <= sy[i] + b; y++) {
                if (0 <= y && y < m) {
                    for (int b = 0; b < 1024 / 64; b++) {
                        mm[y * 16 + b] |= cl[b];
                    }
                }
            }
            if (0 < sx[i] - b || sx[i] + b < n - 1 || 0 < sy[i] - b || sy[i] + b < m - 1) {
                d1 = 0;
            }
        }

        for (int y = 0; y < m; y++) {
            if (memcmp(dl, &mm[y * 16], sizeof(dl)) != 0) {
                d2 = 0;
                break;
            }
        }

        if (d1 || d2) {
            break;
        }
    }

    return b + 1;
}
int main(int q, char ** x)
{
    int m, n, s, r, c;
    while (1) {
        scanf("%d %d %d", &m, &n, &s);
        if (!m && !n && !s) {
            break;
        }

        for (int i = 0; i < s; i++) {
            scanf("%d %d", &r, &c);
            r--;
            c--;
            sx[i] = c;
            sy[i] = r;
        }

        printf("%d\n", al(m, n, s, r, c));
    }
    return 0;
}