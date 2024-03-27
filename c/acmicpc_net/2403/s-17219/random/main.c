#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int max_n = 50;
int max_k = 5;

int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

struct site_t {
    char url[21];
    char password[21];
};

struct site_t sites[100000];

void fill_data(int index)
{
    int length;
    length = get_rand(1, 20);
    for (int l = 0; l < length; l++) {
        int c = get_rand(0, 53);
        if (0 <= c && c <= 25) {
            sites[index].url[l] = 'a' + c;
        } else if (26 <= c && c <= 51) {
            sites[index].url[l] = 'A' + c - 26;
        } else if (c == 52) {
            sites[index].url[l] = '-';
        } else if (c == 53) {
            sites[index].url[l] = '.';
        }
    }
    length = get_rand(1, 20);
    for (int l = 0; l < length; l++) {
        int c = get_rand(0, 25);
        if (0 <= c && c <= 25) {
            sites[index].password[l] = 'A' + c;
        }
    }
}

int main()
{
    int n;
    int m;

    srand(time(NULL));
    n = get_rand(1, 100000);
    m = get_rand(1, 100000);

    memset(sites, 0, sizeof(sites));
    printf("%d %d\n", n, m);

    for (int i = 0; i < n; ) {
        fill_data(i);
        int j;
        for (j = 0; j < i; j++) {
            if (strcmp(sites[j].url, sites[i].url) == 0) {
                break;
            }
        }
        if (j == i) {
            printf("%s %s\n", sites[i].url, sites[i].password);
            i++;
        } else {
            continue;
        }
    }

    for (int i = 0; i < m; i++) {
        int index = get_rand(0, n - 1);
        printf("%s\n", sites[index].url);
    }
    return 0;
}
