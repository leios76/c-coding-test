#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define CW 1
#define CCW -1
int ans;
int N;
typedef struct{
    int SN[8];
    int left, right, chgflag;
}Gear;
Gear gears[5];
void InputData()
{
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            scanf("%1d", &gears[i].SN[j]);
        }
        gears[i].left = 6;
        gears[i].right = 2;
    }
    scanf("%d", &N);

}
void OutputData()
{
   printf("%d\n", ans);
}
// 해당하는 num의 톱니바퀴를 dir 방향으로 회전하는 효과 (left, right)
void Rotate(int num, int dir){
    if(dir == CW){
        gears[num].left = (gears[num].left + 7) % 8;
        gears[num].right = (gears[num].right + 7) % 8;
    }
    else if (dir == CCW){
        gears[num].left = (gears[num].left + 1) % 8;
        gears[num].right = (gears[num].right + 1) % 8;
    }
}
// 3개의 톱니바퀴를 기준 톱니바퀴 num과 회전방향 dir에 따라 인접 극 비교 후 회전 방향 결정 (chgflag)
void Check(int num, int dir){
    switch(num){
        case 1:
        if(gears[1].SN[gears[1].right] != gears[2].SN[gears[2].left]){
            gears[2].chgflag = dir * -1;
            if(gears[2].SN[gears[2].right] != gears[3].SN[gears[3].left]){
                gears[3].chgflag = dir;
                if(gears[3].SN[gears[3].right] != gears[4].SN[gears[4].left]) gears[4].chgflag = dir * -1;
            }
        }
        break;

        case 2:
        if(gears[1].SN[gears[1].right] != gears[2].SN[gears[2].left]) gears[1].chgflag = dir * -1;
        if(gears[2].SN[gears[2].right] != gears[3].SN[gears[3].left]) {
            gears[3].chgflag = dir * -1;
            if(gears[3].SN[gears[3].right] != gears[4].SN[gears[4].left]) gears[4].chgflag = dir;
        }
        break;

        case 3:
        if(gears[3].SN[gears[3].right] != gears[4].SN[gears[4].left]) gears[4].chgflag = dir * -1;
        if(gears[2].SN[gears[2].right] != gears[3].SN[gears[3].left]) {
            gears[2].chgflag = dir * -1;
            if(gears[1].SN[gears[1].right] != gears[2].SN[gears[2].left]) gears[1].chgflag = dir;
        }
        break;

        case 4:
        if(gears[3].SN[gears[3].right] != gears[4].SN[gears[4].left]){
            gears[3].chgflag = dir * -1;
            if(gears[2].SN[gears[2].right] != gears[3].SN[gears[3].left]){
                gears[2].chgflag = dir;
                if(gears[1].SN[gears[1].right] != gears[2].SN[gears[2].left]) gears[1].chgflag = dir * -1;
            }
        }
        break;
    }

}
void Solve()
{
    int num, dir;
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &num, &dir);
        Check(num, dir);
        Rotate(num, dir);
        for (int j = 1; j <= 4; j++)
        {
            if(gears[j].chgflag != 0){
                Rotate(j, gears[j].chgflag);
                gears[j].chgflag = 0;
            }
        }
    }

    for (int i = 1; i <= 4; i++)
    {
        if(gears[i].SN[(gears[i].left + 2) % 8] == 1){
            ans += pow(2, i-1);
        }
    }
}
int main()
{

    InputData();

    Solve();

    OutputData();

    return 0;
}
