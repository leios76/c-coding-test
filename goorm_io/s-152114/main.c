#include <stdio.h>

int main()
{
    int car_count = 0;
    int v;
    int w;
    int max_w[1001];
    int car_number[1001];
    int sum_of_car_number = 0;

    // 무한루프에 빠지지 않도록 하기 위해 최대 100번까지 오류 허용
    scanf("%d", &car_count);

    memset(max_w, 0, sizeof(max_w));
    memset(car_number, 0, sizeof(car_number));

    for (int i = 1; i <= car_count; i++) {
        scanf("%d %d", &v, &w);
        // 내구도가 같거나 높은 차가 있으면 해당 속도의 차량 번호 대체
        if (max_w[v] <= w) {
            max_w[v] = w;

            // 기존의 차량 번호 제거
            sum_of_car_number -= car_number[v];
            car_number[v] = i;

            // 새로운 차량 번호 합산
            sum_of_car_number += i;
        }
    }

    printf("%d\n", sum_of_car_number);
    return 0;
}

