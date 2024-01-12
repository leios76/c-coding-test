#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t p_bitmap[(200 * 1001 + 63) / 64];
uint64_t n_bitmap[(200 * 1001 + 63) / 64];

int main()
{
    int n;
    int s[100000];
    int sum = 0;

    memset(s, 0, sizeof(s));
    memset(p_bitmap, 0, sizeof(p_bitmap));
    memset(n_bitmap, 0, sizeof(n_bitmap));

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
        if (s[i] < 0) {
            n_bitmap[(s[i] * -1) / 64] |= (1ULL << ((s[i] * -1) % 64));
#ifdef DEBUG_OUTPUT
            printf("[%d] set n mask(0x%016llX) value (0x%016lX)\n", s[i], (1ULL << ((s[i] * -1) % 64)), n_bitmap[(s[i] * -1) / 64]);
#endif
        } else if (s[i] > 0) {
            p_bitmap[s[i] / 64] |= (1ULL << (s[i] % 64));
#ifdef DEBUG_OUTPUT
            printf("[%d] set p mask(0x%016llX) value (0x%016lX)\n", s[i], (1ULL << ((s[i]) % 64)), p_bitmap[(s[i]) / 64]);
#endif
        }
    }
    for (int i = 0; i < (200 * 1001 + 63) / 64; i++) {
        uint64_t compare = p_bitmap[i] ^ n_bitmap[i];
        if (compare != 0) {
#ifdef DEBUG_OUTPUT
            printf("%lX\n", compare);
#endif
            for (int j = 0; j < 64; j++) {
                if ((compare & (1ULL << j)) && (p_bitmap[i] & (1ULL << j))) {
#ifdef DEBUG_OUTPUT
                    printf("%d\n", i*64 + j);
#endif
                    sum += i*64 + j;
                }
                if ((compare & (1ULL << j)) && (n_bitmap[i] & (1ULL << j))) {
#ifdef DEBUG_OUTPUT
                    printf("%d\n", i*64 + j);
#endif
                    sum -= i*64 + j;
                }
            }
        }
    }

    printf("%d\n", sum);

    return 0;
}
