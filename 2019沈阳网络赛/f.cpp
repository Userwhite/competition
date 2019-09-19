#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef long long ll;
const int maxn = 5e5+200;

int n,k;ll sum;
int a[maxn];

bool check1(int x){
    int ret=0;
    for(int i=1;i<=n;i++){
        if(a[i]<x)ret+=x-a[i];
    }
    return ret<=k;
}

bool check2(int x){
    int ret=0;
    for(int i=1;i<=n;i++){
        if(a[i]>x)ret+=a[i]-x;
    }
    return ret<=k;
}

int main(){
    while(~scanf("%d%d",&n,&k)){
        sum=0;
        for(int i=1;i<=n;i++)scanf("%d",a+i),sum+=a[i];
        ll minans,maxans;
        int l,r;
        l=0,r=sum/n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check1(mid)){
                minans=mid;
                l=mid+1;
            }
            else r=mid-1;
        }
        r=int(1e9)+100;
        if(sum%n==0)l=sum/n;
        else l=sum/n+1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check2(mid)){
                maxans=mid;
                r=mid-1;
            }
            else l=mid+1;
        }
        printf("%lld\n",maxans-minans);
    }
}
