#include<bits/stdc++.h>
#define fast ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define f(i,a,b) for(int i=a;i<=b;i++)
#define mm make_pair
#define pi 2*acos(0.0)
#define lcm(a,b) (a*b)/__gcd(a,b)
#define Case(i,ans) cout<<"Case "<<i<<": "<<ans<<endl;
#define cp(i,ans) printf("%.if",ans);
#define cpp(i,ans) cout.precision(i);cout<<fixed<<ans<<endl;
#define Y {cout<<"YES"<<endl;return 0;}
#define pb(x) push_back(x)
#define lowbit(x) (x)&(-x)
#define out(x) {cout<<x<<endl;return 0;} 
#define all(v) v.begin(),v.end() 
#define ull unsigned long long
#define mem(x,i) memset(x,i,sizeof(x)) 
#define FOR(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
typedef long long ll;
const ll mod=998244353;
const int inf=0x3f3f3f,maxn=2e5+100;
const int N=2,M=2;
ll gcd(ll x,ll y){if(y==0) return x;else return gcd(y,x%y);} 
ll ksm(ll a,ll b){ll r=1;while(b){if(b&1) r=(r*a)%mod;a=a*a%mod;b>>=1;}return r;} 
unordered_map<ll,ll> mp;
struct Matrix
{
    ll A[N][N];
    int len;
    Matrix(){
        memset(A,0,sizeof(A));
        len = 2;
    }
    Matrix(int lens):len(lens){
        memset(A,0,sizeof(A));
    }
    void einit() {
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
                A[i][j] = (i==j);
    }
    void Creat(int lens)
    {
        len = lens;
        if(len > N) exit(1);
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
            scanf("%lld",&A[i][j]);
    }
    void output()
    {
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<len-1;j++)
                printf("%lld ",A[i][j]);
            printf("%lld\n",A[i][len-1]);
        }
    }
    Matrix operator * (const Matrix &a){
        Matrix ans(len);
        for(int k=0;k<len;k++)
        {
            for(int i=0;i<len;i++) if(A[i][k])
            {
                ll temp;
                for(int j=0;j<len;j++) if(a.A[k][j])
                {
                    temp = (A[i][k]*a.A[k][j]) % mod;
                    ans.A[i][j] = (ans.A[i][j] + temp) % mod;
                    ans.A[i][j]=(ans.A[i][j]+mod)%mod;
                }
            }
        }
        return ans;
    }
    Matrix operator ^ (const ll &b) const { /// 注意运算符号顺序
        Matrix ans(len),a = (*this);ans.einit();
        ll t = b;
        while(t) {
            if(t & 1) ans = ans * a;
            a = a * a;
            t >>= 1;
        }
        return ans;
    }
    void operator = (const Matrix &a){
        len = a.len;
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
            A[i][j] = a.A[i][j];
    }
}base,ans,tmp;
void pre()
{
	base.A[0][0]=3;base.A[0][1]=1;
	base.A[1][0]=2;base.A[1][1]=0;
	ans.A[0][0]=3;ans.A[0][1]=1;
}
int main()
{	
	int t;
	ll n;scanf("%d%lld",&t,&n);
	ll last=n,all=0;
	while(t--)
	{
		n=last;
		ll sum;
		if(mp[n]) sum=mp[n];
		else
		{
			pre();
			if(n==0) sum=0;
			else if(n==1) sum=1;
			else
			{
				ans=ans*(base^(n-2));
				sum=ans.A[0][0];
			}
			mp[n]=sum;
		}
		all^=sum;
		last=n^(sum*sum);
	} 
	printf("%lld\n",all);
	return 0;
}
