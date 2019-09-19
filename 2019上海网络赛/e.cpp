#include<bits/stdc++.h>
using namespace std;
#define ll __int128
//#define ll long long
ll dp[30][30][30][30],k;
vector<char> v;
int check=0;
inline ll read() 
{
    ll X=0,w=1;
    char ch=getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
    while(ch>='0' && ch<='9') X=(X<<3)+(X<<1)+ch-'0',ch=getchar();
    return X*w;
}
void print(ll x)
{
    if(!x) return;
    if(x) print(x/10);
    putchar(x%10+'0');
}
ll dfs(int n,int a,int b,int id)
{
	if(a==n) return dp[n][a][b][id]=1;
	if(dp[n][a][b][id]!=-1) return dp[n][a][b][id];
	ll ans=0;
	for(int i=0;i<=b+1;i++)
	ans+=dfs(n,a+1,max(i,b),i);
	return dp[n][a][b][id]=ans;
}
void dfs1(int n,int a,int b,int id)
{
	int flag=0;
	if(check) return;
	if(((k==1&&a==n+1)||(v.size()==n))&&!check)
	{
		for(int i=0;i<v.size();i++)
		printf("%c",v[i]);
		printf("\n");check=1;
		return;
	} 
	for(int j=0;j<=b;j++)
	{
		if(dp[n][a][b][j]>=k)
		{
			v.push_back(j+'A');
			dfs1(n,a+1,b,j);flag=1;
		}
		else if(dp[n][a][b][j]!=-1) k-=dp[n][a][b][j];
	}
	if(!flag) 
	{
		v.push_back(b+1+'A');
		dfs1(n,a+1,b+1,b+1);
	}
	
}
int n,t;
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("test.out","w",stdout);
	memset(dp,-1,sizeof(dp));
	scanf("%d",&t);
	int num=0;
	while(t--)
	{
		scanf("%d",&n);
		k=read();
		v.clear();
		dfs(n,1,0,0);
		check=0;
		printf("Case #%d: ",++num);
		dfs1(n,1,0,0);
	}
	return 0;
}
