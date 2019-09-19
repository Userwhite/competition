#include<bits/stdc++.h>
#define ull unsigned long long
using namespace std;
const int mod=1e9+7;
const int maxn=1e5+100;
int t,m;
ull pr=131,p[100];
char s[maxn];
unordered_map<ull,int>mp[26][26];
ull Hash[maxn];
vector<int> v;
char q[maxn];
pair<int,int> pp[maxn];
void pre()
{
	p[0]=1;
	for(int i=1;i<=30;i++) p[i]=p[i-1]*pr;
}
void solve(int x)
{
	int len=strlen(s+1);
	ull sum=0;
	for(int i=1;i<=x;i++)
	{
		sum+=p[s[i]-'a'];
	}
	if(mp[s[1]-'a'][s[x]-'a'].count(sum)) {mp[s[1]-'a'][s[x]-'a'][sum]++;}
	for(int i=x+1;i<=len;i++)
	{
		sum-=p[s[i-x]-'a'];
		sum+=p[s[i]-'a'];
		if(mp[s[i-x+1]-'a'][s[i]-'a'].count(sum)) {mp[s[i-x+1]-'a'][s[i]-'a'][sum]++;}
	} 
}
int main()
{
	pre();
	scanf("%d",&t);
	while(t--)
	{
		scanf("%s",s+1);
		scanf("%d",&m);
		for(int i=0;i<26;i++)
		for(int j=0;j<26;j++) mp[i][j].clear();
		int mx=0;v.clear();
		for(int i=1;i<=m;i++)
		{
			scanf("%s",q+1);
			int len=strlen(q+1);
			ull tmp=0;
			for(int j=1;j<=len;j++) tmp+=p[q[j]-'a'];
			v.push_back(len);
			mp[q[1]-'a'][q[len]-'a'][tmp]=1;Hash[i]=tmp;
			pp[i]=make_pair(q[1]-'a',q[len]-'a');
		}
		sort(v.begin(),v.end());
		v.erase(unique(v.begin(),v.end()),v.end());
		for(int i=0;i<v.size();i++)
		{
			solve(v[i]);
		}
		for(int i=1;i<=m;i++)
		printf("%d\n",mp[pp[i].first][pp[i].second][Hash[i]]-1);
	}
	return 0;
} 
/*
1
abccdefgdaaacdcdfegaada
5
gadaa
abccd
defg
aa
aa
*/
