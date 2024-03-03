#include <stdio.h>
#include <math.h>
int main() {
int t,x,y,m,r,v;
scanf("%d",&t);
for (int i = 0; i < t; i++) {
scanf("%d %d",&x,&y);
m=(sqrt(1+4ULL*(y-x))-1)/2;
r=y-x-(m*(m+1));
v=m*2;
while (r>0) { r -= (m + 1); v++; }
printf("%d\n", v);
}
return 0;
}
