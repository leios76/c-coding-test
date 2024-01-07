#include <stdio.h>
int main() {
	int *glass;
	int *sum;
	int n;
	int q_count;
	int v;
	int q;
	int a;
	int b;
	int output;
	int size = 256;
	int sum_size = 0;
	
	scanf("%d %d", &n, &q_count);

	glass = (int *)malloc(sizeof(int) * n);
	memset(glass, 0, sizeof(int)*n);
	
	sum_size = (n + size - 1)/size;
	sum = (int *)malloc(sizeof(int) * sum_size);
	memset(sum, 0, sizeof(int) * sum_size);

	for (int i = 0; i < n; i++) {
		scanf("%d", &glass[i]);
		sum[i/size] += glass[i];
	}
		
	for (int i = 0; i < q_count; i++) {
		scanf("%d %d %d", &q, &a, &b);
		a--;
		switch (q) {
			case 1:
				output = 0;
				for (int j = a; j < b; j++) {
					if ((j % size == 0) && j + size < b) {
						output += sum[j/size];
						j += (size - 1);
					} else {
						output += glass[j];						
					}
				}
				printf("%d\n", output);
				break;
			case 2:
					glass[a] += b;
				sum[a/size] += b;
				break;
			case 3:
					glass[a] -= b;
				sum[a/size] -= b;
				break;
		}
	}
	
	free(glass);
	
	return 0;
}

