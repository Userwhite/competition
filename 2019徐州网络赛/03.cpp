#include<bits/stdc++.h>
using namespace std;

int main(){
    int w;cin>>w;
    bool ok=false;
    for(int i=2;i<=100;i+=2){
        for(int j=2;j<=100;j+=2){
            if(i+j==w)ok=true;
        }
    }
    if(ok)puts("YES");
    else puts("NO");
}
