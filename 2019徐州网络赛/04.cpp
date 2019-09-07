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
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
ll gcd(ll x,ll y){if(y==0) return x;else return gcd(y,x%y);} 
ll ksm(ll a,ll b){ll r=1;while(b){if(b&1) r=(r*a)%mod;a=a*a%mod;b>>=1;}return r;} 
void exgcd(ll a,ll b,ll& d,ll& x,ll& y) {if(!b){d=a;x=1;y=0;} else{exgcd(b,a%b,d,y,x);y-=x*(a/b);}}
ll inv(ll a, ll p) {ll d,x,y;exgcd(a,p,d,x,y);return d==1?(x+p)%p:-1;}
const int maxn=1e5+100;
int n,m,k,q;  
char t[maxn],s[maxn];
int l1,l2;
ull st[maxn],ss[maxn],p[maxn],pr=131;
void pre()
{
	st[0]=0;p[0]=1;
	for(int i=1;i<maxn;i++) p[i]=p[i-1]*pr; 
	for(int i=1;i<=l1;i++)
	{
		st[i]=st[i-1]*pr+t[i];
	}
}
void work()
{
	ss[0]=0;
	for(int i=1;i<=l2;i++)
	{
		ss[i]=ss[i-1]*pr+s[i];
	}
}
ull queryt(int l,int r)
{
	return st[r]-st[l-1]*p[r-l+1];
} 
ull querys(int l,int r)
{
	return ss[r]-ss[l-1]*p[r-l+1];
} 
int main()
{
	scanf("%s",t+1);
	l1=strlen(t+1);
	pre();
	scanf("%d",&q);
	while(q--)
	{
		scanf("%s",s+1);
		l2=strlen(s+1);
		work();
		if(l1>=l2)
		{
			ull tmp=querys(1,l2);
			int flag=0;
			for(int i=l2;i<=l1;i++)
			{
				if(queryt(i-l2+1,i)==tmp)
				{
					flag=1;
					break;
				}
			}
			if(flag)
			{
				if(l1==l2) printf("jntm!\n");
				else printf("my child!\n");
			}
			else
			{
				if(l1==l2) printf("friend!\n");
				else printf("oh, child!\n");
			}
		}
		else
		{
			ull tmp=queryt(1,l1);
			int flag=0;
			for(int i=l1;i<=l2;i++)
			{
				if(querys(i-l1+1,i)==tmp)
				{
					flag=1;
					break;
				}
			}
			if(flag) printf("my teacher!\n");
			else printf("senior!\n");
		}
	}
	return 0;
}
