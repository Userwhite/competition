#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define inf 0x3f3f3f3f
using namespace std;

const int maxn=1e6+100;

int to[maxn][26];
int dp[maxn],n,m;
char a[maxn],b[maxn];

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s%s",a+1,b+1);
    a[0]='#',b[0]='#';
    for(int i=0;i<26;i++){
        int pre=-1;
        for(int j=n;j>=0;j--){
            to[j][i]=pre;
            if(a[j]==char('a'+i))pre=j;
        }
    }
    int now=0,ans=-1;
    dp[0]=0;
    for(int i=1;i<=m;i++){
        if(now==-1){
            dp[i]=-1;
            continue;
        }
        now=to[now][b[i]-'a'];
        if(now==-1){
            dp[i]=-1;
            continue;
        }
        dp[i]=now;
    }
    if(now!=-1){
        if(n-now>0)ans=max(ans,m+n-now);
    }
    for(int i=1;i<=m;i++){
        if(dp[i-1]==-1)continue;
        int tmp=dp[i-1],L;
        for(int j=b[i]-'a'+1;j<26;j++){
            L=to[tmp][j];
            if(L==-1)continue;
            ans=max(ans,i+n-L);
        }
    }
    cout<<ans<<endl;
}
