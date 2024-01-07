#include <stdio.h>
//#define CHECK_BOUNDARY

int main() {
	int car_count = 0;
	int v;
	int w;
	int max_w[1001];
	int car_number[1001];
	int sum_of_car_number = 0;
	
	// 무한루프에 빠지지 않도록 하기 위해 최대 100번까지 오류 허용
	for (int i = 0; i < 100; i++) {
		scanf("%d",&car_count);
		#ifdef CHECK_BOUNDARY
		if (car_count  < 1 || car_count > 2000000) {
			printf("Car count must be greater than 1 and less than 2000000\n");
			continue;
		}
		#endif
		break;
	}
	
	#ifdef CHECK_BOUNDARY
	// 100번 넘게 오류가 발생한 경우에는 에러 처리
	if (car_count == 0) {
		printf("Too many errors\n");
		return -1;
	}
	#endif
	
	memset(max_w, 0, sizeof(max_w));
	memset(car_number, 0, sizeof(car_number));
	
	for (int i = 1; i <= car_count; i++) {
		scanf("%d %d", &v, &w);
		#ifdef CHECK_BOUNDARY
		if (v < 1 || v > 1000) {
			printf("v must be greater than 1 and less than 1000\n");
			continue;			
		}
		if (w < 1 || w > 1000000000) {
			printf("w must be greater than 1 and less than 1000000000\n");
			continue;			
		}
		#endif
		
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

