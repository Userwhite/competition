#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <vector>
#include <stack>
#include <limits.h>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>
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
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
ll gcd(ll x,ll y){if(y==0) return x;else return gcd(y,x%y);} 
ll ksm(ll a,ll b){ll r=1;while(b){if(b&1) r=(r*a)%mod;a=a*a%mod;b>>=1;}return r;} 
void exgcd(ll a,ll b,ll& d,ll& x,ll& y) {if(!b){d=a;x=1;y=0;} else{exgcd(b,a%b,d,y,x);y-=x*(a/b);}}
ll inv(ll a, ll p) {ll d,x,y;exgcd(a,p,d,x,y);return d==1?(x+p)%p:-1;}
const int maxn=1e5+100;
int n,m,k,t;  
map<pair<double,double>,int>mp,mq;
struct qw
{
	double x,y;
    bool operator == (const qw & rhs) const{
        return x == rhs.x && y == rhs.y;
    }
}a[maxn];
int main()
{
	scanf("%d",&n);
	int cnt=0;
	FOR(i,1,n) 
	{
		double x,y;
		scanf("%lf%lf",&x,&y);
		if(!mq[mm(x,y)]) a[++cnt]=(qw){x,y}; 
		mq[mm(x,y)]++;
	}
	int ans=1E9;
	FOR(i,1,cnt)
	FOR(j,i+1,cnt)
	{
		double x=(a[i].x+a[j].x)/2.0,y=(a[i].y+a[j].y)/2.0;
		mp[mm(x,y)]+=mq[mm(a[i].x,a[i].y)]+mq[mm(a[j].x,a[j].y)];
	}
	for(auto it:mp)
	{
		ans=min(ans,n-it.second-mq[it.first]);
	}
	for(int i=1;i<=cnt;i++)
	{
		ans=min(ans,n-mq[mm(a[i].x,a[i].y)]);
	}
	printf("%d\n",ans);
}
