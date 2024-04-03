#include<bits/stdc++.h>
using namespace std;
int n,m;
int used[14];
int arr[14];
void backtracking (int k){
    if(k==m){
        for(int i=0;i<m;i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
        return;
    }

    for(int i=1;i<=n;i++){
        if(!used[i] and (arr[k-1]<i)){ //k가 0일때는 음수 인덱스라 오류?
            arr[k]=i;
            used[i]=1;
            backtracking(k+1);
            used[i]=0;
        }
    }

}
int main(){
    cin>>n>>m;
    backtracking(0);
}