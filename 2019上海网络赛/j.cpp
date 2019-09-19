#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef long long ll;
const int maxn = 1e6+200;

int dp[310][151110];
int A[350],last[350];

const int mod = 1e9+7;
inline int read(){int num=0,w=0;char ch=0;while(!isdigit(ch)){w|=ch=='-';ch=getchar();}while(isdigit(ch))
{num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}return w? -num: num;}

inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9)write(x / 10);putchar(x % 10 + '0');}

int main(){
    int T,n;cin>>T;
    while(T--){
        n=read();
        int sum=0;
        for(int i=1;i<=n;i++)A[i]=read(),sum+=A[i];
        for(int i=1;i<=n+1;i++)last[i]=0;
        sort(A+1,A+1+n);
        for(int i=n;i>=1;i--)last[i]=last[i+1]+A[i];
        for(int i=1;i<=n;i++)for(int j=0;j<=last[i];j++)dp[i][j]=0;
        dp[n][A[n]]=1;
        dp[n][0]=1;
        for(int i=n-1;i>=1;i--){
            for(int j=0;j<=last[i+1];j++){
                if(dp[i+1][j]){
                    dp[i][j+A[i]]=(1ll*dp[i][j+A[i]]+1ll*dp[i+1][j])%mod;
                    dp[i][j]=(1ll*dp[i][j]+1ll*dp[i+1][j])%mod;
                }
            }
        }
        ll ans=0;
        if(A[n]>=sum-A[n]&&A[n]-A[n]<=sum-A[n])ans=1;
        for(int i=1;i<=n-1;i++){
            for(int j=0;j<=last[i+1]&&j+A[i]<=(sum+A[i])/2;j++)if(dp[i+1][j]&&2*(j+A[i])>=sum){
                ans=(ans+1ll*dp[i+1][j])%mod;
            }
        }
        printf("%lld\n",ans);
    }
}
