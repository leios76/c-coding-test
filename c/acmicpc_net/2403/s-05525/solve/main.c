#include <stdio.h>
int main()
{
    int N;
    int M;

    int r = 0;
    char c = 0;
    char p = 0;
    int i;
    scanf("%d", &N);
    scanf("%d", &M);

    i = M;
    for (int m = 0; m < M; m++) {
        c = getchar();
        if (c != 'I' && c != 'O') {
            m--;
            continue;
        }
        if (p == c) {
            i = M;
        }
        if (c == 'I') {
            if (i == M) {
                i = m;
            } else if (m - i == N * 2) {
                r++;
                i += 2;
            }
        }
        p = c;
    }
    printf("%d\n", r);
    return 0;
}
