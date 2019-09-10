#include<bits/stdc++.h>
#define ls p<<1
#define rs p<<1|1 
#define fast ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define mm make_pair
#define pi 2*acos(0.0)
#define lcm(a,b) (a*b)/__gcd(a,b)
#define cp(i,ans) primeintf("%.if",ans);
#define cpp(i,ans) cout.primeecision(i);cout<<fixed<<ans<<endl;
#define lowbit(x) (x)&(-x)
#define out(x) {cout<<x<<endl;return 0;} 
#define all(v) v.begin(),v.end() 
#define mem(x,i) memset(x,i,sizeof(x)) 
#define eps 1e-8 
#define ull unsigned long long
using namespace std;
typedef long long ll;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
//ll gcd(ll x,ll y){if(y==0) return x;else return gcd(y,x%y);} 
ll ksm(ll a,ll b,ll mod){ll r=1;while(b){if(b&1) r=(r*a)%mod;a=a*a%mod;b>>=1;}return r;} 
const int maxn=1e5+100;
ll n,k,t,m[10]={13,17,19,23,29,31},a[10];  
ll str[1000]; 
vector<ll> g[10];
int tot=6;
ll ans=2E9;
ll gcd(ll a, ll b, ll &d, ll &x, ll &y)
{
	if(!b)
		d=a,x=1,y=0;
	else
		gcd(b,a%b,d,y,x),y-=x*(a/b);
}
bool check(int p,int v)
{
	for(int i=p;i<100;i+=v)
	if(str[i]%(v-1)) return 0;
	return 1;
}
ll phi(ll x)
{
	ll res=x;
	if(x==1) return 1;
	for(int i=2;i*i<=x;i++)
	{
		if(x%i==0)
		{
			res=res/i*(i-1);
			while(x%i==0) x/=i;
		}
	}
	if(x>1) res=res/x*(x-1);
	return res;
}
bool judge(ll x)
{
	FOR(i,0,99)
	{
		if(str[i]!=phi(x+i)) return 0;
	}
	return 1;
}
ll CRT()
{
	ll M=1,ans=0,d,y;
	FOR(i,0,tot-1) M*=m[i];
	FOR(i,0,tot-1)
	{
		ll w=M/m[i];
		gcd(m[i],w,d,d,y);
		ans=(ans+a[i]*w*y)%M;
	}
	ans=(ans+M)%M;
	if(ans<1) ans+=M;
	if(judge(ans)) return ans;
	if(ans+M+99<=1E8+5E7&&judge(ans+M)) return ans+M;
	return 2E9;
}
void dfs(int x)
{
	if(x==tot)
	{
		ans=min(ans,CRT());
		return ;
	}
	for(int i=0;i<g[x].size();i++)
	{
		a[x]=g[x][i];
		dfs(x+1);
	}
}
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("test.out","w",stdout);
	cin>>t;
	while(t--)
	{
        ans = 2E9;
		FOR(i,0,99) cin>>str[i];
		ll res=1;
		for(int i=0;i<tot;i++)
		{
			g[i].clear();
			for(int j=0;j<m[i];j++)
			{
				if(check(j,m[i])) 
				g[i].push_back((m[i]-j)%m[i]);
			}
			res*=g[i].size();
		}
		if(res>10000) {cout<<"NO\n";continue;} 
		dfs(0);
		if(ans==2E9) cout<<"NO\n";
		else cout<<"YES\n"<<ans<<endl;
	}
}
/*

*/
