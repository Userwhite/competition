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
//typedef __int128 ll;
typedef long long ll;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
inline ll read(){
    ll x=0,f=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){
        if(ch=='-')
            f=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}
inline void print(ll x){
    if(x<0){
        putchar('-');
        x=-x;
    }
    if(x>9)
        print(x/10);
    putchar(x%10+'0');
}

ll gcd(ll a, ll b, ll &d, ll &x, ll &y)
{
	if(!b)
		d=a,x=1,y=0;
	else
		gcd(b,a%b,d,y,x),y-=x*(a/b);
}
ll ksm(ll a,ll b){ll r=1;while(b){if(b&1) r=(r*a)%mod;a=a*a%mod;b>>=1;}return r;} 
void exgcd(ll a,ll b,ll& d,ll& x,ll& y) {if(!b){d=a;x=1;y=0;} else{exgcd(b,a%b,d,y,x);y-=x*(a/b);}}
ll inv(ll a, ll p) {ll d,x,y;exgcd(a,p,d,x,y);return d==1?(x+p)%p:-1;}
const int maxn=1e6+100;
int n,k,t;
ll sum[maxn],m[100],a[100];
ll mx=1000000000000000,mi=1;
void pre()
{
	sum[0]=0;sum[1]=1;
	for(int i=2;;i++)
	{
		sum[i]=sum[i-1]+sum[i-2]+1;
		if(sum[i]>mx) break;
	}
}
int check(ll x)
{
	ll ans=3;
	for(int i=1;;i++)
	{
		if(ans>=x) return 0;
		ans+=sum[i];
		if(ans>=x) return 1;
		ans+=1;
	}
	return 0;
}
void ex_gcd(ll a,ll b,ll &d,ll &x,ll &y)//扩展欧几里得
{
    if(!b) {d=a;x=1;y=0;}
    else{
        ex_gcd(b,a%b,d,y,x);
        y-=x*(a/b);
    }
}
ll ex_crt(ll *m,ll *r,int n)
{
    ll M=m[1],R=r[1],x,y,d;
    for(int i=2;i<=n;i++){
        ex_gcd(M,m[i],d,x,y);
        if((r[i]-R)%d) return -1;
        x=(r[i]-R)/d*x%(m[i]/d);
        R+=x*M;
        M=M/d*m[i];
        R%=M;
    }
    return R>=2?R:R+M;
}
int main()
{
	pre();
	//int x;while(cin>>x) cout<<check(x)<<endl;
	k=read();
	for(int i=1;i<=k;i++)
	{
		m[i]=read();a[i]=read();
	}
	ll ans=ex_crt(m,a,k);
	if(ans<0||ans>mx) cout<<"Tankernb!\n";
	else cout<<(check(ans)?"Zgxnb!\n":"Lbnb!\n");
}
