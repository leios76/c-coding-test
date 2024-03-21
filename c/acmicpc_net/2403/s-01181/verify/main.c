#include <stdio.h>
#include <string.h>

void mergeSort(char str[][51], int p, int r, int w);
void merge(char str[][51], int p, int q, int r, int w);

int main()
{
    int cnt, t = 0, tcnt = 0, len = 0, tlen = 0;
    char str[20001][51], s[51];
    scanf("%d", &cnt);

    for (int i = 0; i < cnt; i++) {
        scanf("%s", s);
        if (i == 0) {
            strcpy(str[i], s);
        } else {
            for (int j = 0; j < i; j++) {
                if (strcmp(s, str[j]) == 0) {
                    t = 1;
                    tcnt++;
                    break;
                }
            }
            if (t != 1) {
                strcpy(str[i - tcnt], s);
            }
            t = 0;
        }
    }
    len = cnt - tcnt;

    mergeSort(str, 0, len - 1, 0);

    if (strlen(str[0]) == strlen(str[len - 1])) {
        mergeSort(str, 0, len - 1, 1);
    } else {
        for (int i = 0; i < len - 1; i++) {
            if ((strlen(str[i]) == strlen(str[i + 1])) && tlen != strlen(str[i])) {
                for (int j = i + 1; j <= len; j++) {
                    if (strlen(str[i]) != strlen(str[j])) {
                        tlen = strlen(str[i]);
                        mergeSort(str, i, j - 1, 1);
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < len; i++) {
        printf("%s\n", str[i]);
    }
}

void mergeSort(char str[][51], int p, int r, int w)
{
    int q;
    if (p < r) {
        q = (p + r) / 2;
        mergeSort(str, p, q, w);
        mergeSort(str, q + 1, r, w);
        merge(str, p, q, r, w);
    }
}

void merge(char str[][51], int p, int q, int r, int w)
{
    int i = p, j = q + 1, k = p;
    char tmp[20001][51];
    if (w == 0) {
        while (i <= q && j <= r) {
            if (strlen(str[i]) < strlen(str[j])) {
                strcpy(tmp[k], str[i]);
                i++;
            } else {
                strcpy(tmp[k], str[j]);
                j++;
            }
            k++;
        }
    } else {
        while (i <= q && j <= r) {
            if (strcmp(str[i], str[j]) < 0) {
                strcpy(tmp[k], str[i]);
                i++;
            } else {
                strcpy(tmp[k], str[j]);
                j++;
            }
            k++;
        }
    }

    while (i <= q) {
        strcpy(tmp[k], str[i]);
        k++;
        i++;
    }
    while (j <= r) {
        strcpy(tmp[k], str[j]);
        k++;
        j++;
    }
    for (int a = p; a <= r; a++) {
        strcpy(str[a], tmp[a]);
    }
}