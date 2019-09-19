#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1 
#define fast ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define mm make_pair
#define pi 2*acos(0.0)
#define lcm(a,b) (a*b)/__gcd(a,b)
#define cp(i,ans) printf("%.if",ans);
#define cpp(i,ans) cout.precision(i);cout<<fixed<<ans<<endl;
#define lowbit(x) (x)&(-x)
#define out(x) {cout<<x<<endl;return 0;} 
#define all(v) v.begin(),v.end() 
#define mem(x,i) memset(x,i,sizeof(x)) 
#define mec(x,y) memcpy(x,y,sizeof(y))
#define eps 1e-8 
#define ull unsigned long long
using namespace std;
typedef long long ll;
const ll mod=1e9+7;
const int inf=0x3f3f3f3f;
ll gcd(ll x,ll y){if(y==0) return x;else return gcd(y,x%y);} 
ll ksm(ll a,ll b){ll r=1;while(b){if(b&1) r=(r*a)%mod;a=a*a%mod;b>>=1;}return r;} 
void exgcd(ll a,ll b,ll& d,ll& x,ll& y) {if(!b){d=a;x=1;y=0;} else{exgcd(b,a%b,d,y,x);y-=x*(a/b);}}
ll inv(ll a, ll p) {ll d,x,y;exgcd(a,p,d,x,y);return d==1?(x+p)%p:-1;}
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const int maxn=10000;
int n,m,k,t;
vector<vector<int> >fac[5005];
vector<int> v;  
void dfs(int last,int pos,int len,int pro,int sum)
{
    if(pos==len+1)
    {
        int num=pro-sum+v.size();
        if(num<=3000) fac[num].push_back(v);
        return;
    }
    int up=6000/pro;
    if(up<last) return;
    for(int i=last;i<=up;i++)
    {
        v.push_back(i);
        dfs(i,pos+1,len,pro*i,sum+i);
        v.pop_back();
    }
}
ll C(ll n,ll m){
    static ll M = 0,inv[maxn],mul[maxn],invMul[maxn];
    while(M <= n){
        if (M){
            inv[M] = M == 1 ? 1 : (mod-mod/M)*inv[mod%M]%mod;
            mul[M] = mul[M-1]*M%mod;
            invMul[M] = invMul[M-1]*inv[M] % mod;
        }else{
            mul[M] = 1;
            invMul[M] = 1;
        }
        M++;
    }
    return mul[n]*invMul[m] % mod * invMul[n-m]%mod;
}
int used[10000];
ll cnt[10000];
ll ans;
int main()
{
    for(int i=2;i<=12;i++) {
        v.clear();
        dfs(2,1,i,1,0);
    }
    int T;
    scanf("%d",&T);
    while(T--){
        int x;
        x = read();
        ll ans1 = 0;
        for(auto it:fac[x]){
            ans = 1;
            int res = x;
            memset(used,0,sizeof(used));
            memset(cnt,0,sizeof(cnt));
            for(auto iy:it) cnt[iy]++;
            for(auto iy:it) {
                if (used[iy]) continue;
                used[iy] = 1;
                ans = (ans * C(res,cnt[iy])) % mod;
                res -= cnt[iy];
            }
            ans1 = (ans1 + ans) % mod;
        }
        printf("%lld\n",ans1);
    }
    return 0;
}
