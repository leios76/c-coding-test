#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int height;
    int time;
}flattenInfo; //각 층별로 몇층에서 얼마의 시간이 걸리는지 저장하기 위한 구조체

typedef struct {
    int g;
    int s;
    int **array;
    int inventory;
}mapInfo; //맵의 크기, 인벤토리의 블록개수 등 초기 정보를 저장하기 위한 구조체

int checkTime(int height, int **array, mapInfo *map);
int getLeastTime(flattenInfo *a, int size);

int main(void)
{
    mapInfo a;
    flattenInfo *ps;
    int size;
    int index;
    int max = 0;
    int min = 256;

    scanf("%d %d %d", &a.s, &a.g, &a.inventory); //맵의 크기, 인벤토리에 관한 정보를 입력받는다.
    a.array = (int **)calloc(sizeof(int *), a.s); //맵의 높이를 입력받을 배열을 사용하기 위해 메모리를 할당한다.
    for (int i = 0; i < a.s; i++) {
        a.array[i] = (int *)calloc(sizeof(int), a.g);
    }
    for (int i = 0; i < a.s; i++) { //이차원배열을 좌표평면처럼 이용한다. 각 좌표의 높이를 입력받고 max height와 min height를 구한다.
        for (int j = 0; j < a.g; j++) {
            scanf("%d", &a.array[i][j]);
            if (a.array[i][j] > max) {
                max = a.array[i][j];
            }
            if (a.array[i][j] < min) {
                min = a.array[i][j];
            }
        }
    }
    ps = (flattenInfo *)calloc(sizeof(flattenInfo), max - min + 1); //각 층의 정보를 저장할 구조체 배열 선언

    size = max - min + 1; //모든 층에 대해서 블록이 부족하지 않는 경우도 있으니 size를 기본적으로 설정해준다.
    for (int i = min; i <= max; i++) {
        int temp = checkTime(i, a.array, &a);

        if (temp != -1) { //블록의 부족함 없이 잘 평탄화 할 수 있을때
            ps[i - min].height = i;
            ps[i - min].time = temp;
        } else { //처음으로 블록이 부족해지면...
            size = i - min;
            //가장 마지막에 확인한 층수는 블록개수 부족으로 배열에 저장되지 않았다. ex) 3층부터 살펴보던 중 8층에서 블록이 부족해지면 3층부터 7층까지 총 5개층이 배열이 입력된 것이다. 따라서 사이즈는 i - min
            break;
        }
        //목표하는 높이가 높아질수록, 깎아내는 블록은 적어지고 쌓아야하는 블록의 개수는 늘어난다. 따라서 a층에서 블록이 부족하면, a층 이상에서는 무조건 블록이 부족해지므로 살펴볼 필요도 없다. 따라서 블록이 부족해지면 반복문을 벗어난다.
    }
    //최소시간, 최대높이를 가지는 인덱스를 확인하는 용도
    index = getLeastTime(ps, size);
    //printf("%d\n",index);
    printf("%d %d\n", ps[index].time, ps[index].height);
    free(ps); free(a.array);

    return 0;
}

int checkTime(int height, int **array, mapInfo *map)
{
    int quantity = map->inventory;
    int time = 0;
    int temp;

    for (int i = 0; i < map->s; i++) {
        for (int j = 0; j < map->g; j++) {
            if (array[i][j] <= height) { //높이가 목표 높이보다 낮거나 같을때
                temp = height - array[i][j];
                quantity -= temp;
                time += temp;
            } else { //높이가 목표 높이보다 높을떄
                temp = array[i][j] - height;
                quantity += temp;
                time += temp * 2;
            }
        }
    }

    //각 목표 높이마다 시간이 잘 계산 되는지 확인하는 용
    //printf("목표 높이가 %d층 일때 %d초 남은블럭 %d개\n",height,time,quantity);
    if (quantity < 0) { //블럭이 모자라면 -1을 반환햔다.
        return -1;
    } else {
        return time;
    }
}

int getLeastTime(flattenInfo *a, int size)
{
    int min = a[0].time;
    for (int i = 1; i < size; i++) {
        if (a[i].time < min) {
            min = a[i].time;
        }
    }
    for (int i = size - 1; i >= 0; i--) {
        if (a[i].time == min) {
            return i;
        }
    }
    exit(-1);
}

