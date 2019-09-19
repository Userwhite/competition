#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef long long ll;
const int maxn = 3e4+200;

int n,m;
ll dp[maxn];
struct node{
    int p,c;
    bool operator<(const node &x)const
    {
    	if(p!=x.p) return p<x.p;
    	else return c>x.c;
	}
}A[5050];

int main(){
    while(~scanf("%d%d",&n,&m)){
        int w=m,ind=0x3f3f3f3f,indd=0x3f3f3f3f;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&A[i].p,&A[i].c);
        }
        sort(A+1,A+1+n);
        for(int j=0;j<=m+10005;j++) dp[j]=1E18;
		dp[0]=0; 
        for(int j=0;j<=m+10005;j++)
        for(int i=1;i<=n;i++)
        {
        	if(A[i].c>j) break;
        	dp[j]=min(dp[j],dp[j-A[i].c]+A[i].p);
		}
		ll ans=1E18,b=0;
		for(int j=m;j<=m+10005;j++)
		{
			if(ans>=dp[j]) ans=dp[j],b=j;
		}
		printf("%lld %lld\n",ans,b);
    }
    return 0;
}
