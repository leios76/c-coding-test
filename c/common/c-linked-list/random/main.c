#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 20;
int min_n = 1;

int max_len = 50;
int min_len = 1;

int max_ch = 5;

int main()
{
    int n;
    int len;

    srand(time(NULL));
    n = rand() % (max_n - min_n + 1) + min_n;

    printf("%d\n", n);

    for (int i = 0; i < n; i++) {
        len = rand() % (max_len - min_len + 1) + min_len;
        for (int l = 0; l < len; l++) {
            int ch = rand() % max_ch;
            printf("%c", 'a' + ch);
        }
        printf("\n");
    }
    return 0;
}
