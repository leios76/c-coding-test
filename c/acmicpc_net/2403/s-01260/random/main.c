#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main()
{
    int n;
    int m;
    int v;
    int s;
    int e;

    srand(time(NULL));
    n = get_rand(1, 1000);
    m = get_rand(1, 10000);
    v = get_rand(1, n);

    printf("%d %d\n", n, m, v);

    for (int i = 1; i <= m;) {
        s = get_rand(1, n);
        e = get_rand(1, n);
        if (s == e) {
            continue;
        }
        printf("%d %d\n", s, e);
        i++;
    }
    return 0;
}
