#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef DEBUG_OUTPUT
    #define debug(...)  printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

int dp[1000001];

int get_dp(int n, int dup)
{
    int min_count = 0x7FFFFFF;
    int count;
    int value;
    int repeat;
    if (dp[n] != -1) {
        return dp[n];
    }
    if (n == 1) {
        return 0;
    }

    if ((n % 3) == 0) {
        value = n;
        repeat = 0;
        while ((value % 3) == 0) {
            value = value / 3;
            repeat++;
        }
        count = repeat + get_dp(value, 0);
        if (min_count > count) {
            min_count = count;
        }
    }
    if ((n % 2) == 0) {
        value = n;
        repeat = 0;
        while ((value % 2) == 0) {
            value = value / 2;
            repeat++;
        }
        count = repeat + get_dp(value, 0);
        if (min_count > count) {
            min_count = count;
        }
    }

    count = 1 + get_dp(n - 1, dup + 1);
    if (min_count > count) {
        min_count = count;
    }

    dp[n] = min_count;
    return dp[n];
}

int main(int argc, char ** argv)
{
    int n;
    memset(dp, -1, sizeof(dp));
    scanf("%d", &n);
    printf("%d\n", get_dp(n, 0));
    return 0;
}
