#include <stdio.h>

int main(void)
{
    int n;
    int dp[303] = { 0 };
    int one[303] = { 0 }, two[303] = { 0 };
    int one_[303] = { 0 }, two_[303] = { 0 };
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &dp[i]);
    }
    one[1] = dp[1];
    one[2] = dp[2];
    two[1] = dp[1];
    two[2] = dp[1] + dp[2];
    for (int i = 3; i <= n; i++) {
        one[i] = dp[i] + (two[i - 2] > two_[i - 2] ? two[i - 2]:two_[i - 2]);
        two[i] = dp[i] + one[i - 1];
        two_[i] = dp[i] + (two[i - 2] > two_[i - 2] ? two[i - 2] : two_[i - 2]);
    }
    if (two[n] <= one[n] && two_[n] <= one[n]) {
        printf("%d\n", one[n]);
    } else if ((one[n] <= two[n] && two_[n] <= two[n])) {
        printf("%d\n", two[n]);
    } else {
        printf("%d\n", two_[n]);
    }
}