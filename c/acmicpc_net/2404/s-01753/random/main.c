#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


struct road_t {
    int s;
    int e;
};

struct road_t backup[300000];
int backup_count = 0;

int get_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

int main()
{
    int V;
    int E;
    int K;

    srand(time(NULL));
    //V = get_rand(1, 20000);
    //E = get_rand(1, 300000);
    V = get_rand(1, 15);
    E = get_rand(1, 30);
    K = get_rand(1, V);

    printf("%d %d\n%d\n", V, E, K);
    for (int e = 0; e < E; e++) {
        int s = get_rand(1, V);
        int e = get_rand(1, V);
        int w = get_rand(1, 10);
        if (s == e) {
            continue;
        }
        int found = 0;
        for (int b = 0; b < backup_count; b++) {
            if (backup[b].s == s && backup[b].e == e || backup[b].s == e && backup[b].e == s) {
                found = 1;
                break;
            }
        }
        if (found) {
            continue;
        }
        backup[backup_count].s = s;
        backup[backup_count].e = e;
        backup_count++;

        printf("%d %d %d\n", s, e, w);
    }

    return 0;
}
