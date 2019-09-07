#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll mod = 1e9+7;
const int maxn = 1e6+100;
vector<int>G[maxn];
ll dp[maxn];
int ans;

inline ll quick_pow(ll x,int p){
    ll res=1;
    while(p){
        if(p&1) res=(res*x)%mod;
        x=(x*x)%mod, p>>=1;
    }
    return res;
}

inline ll inv(ll a){
    ll inv_a=quick_pow(a,mod-2);
    return inv_a;
}

void dfs(int u,int f,int d){
    int k=0;
    for(auto v:G[u]){
        if(v==f)continue;
        k++;
        dfs(v,u,d+1);
    }
    ll ret=0,T=1,nvk;
    if(k)nvk=inv(k);
    for(auto v:G[u]){
        if(v==f)continue;
        ret=(ret+dp[v]*nvk%mod)%mod;
    }
    if(k){
        ret=(1-ret+mod)%mod;
        for(int i=1;i<=k;i++){
            T=T*ret%mod;
        }
        dp[u]=(1-T+mod)%mod;
    }
    else {
        if(d==ans)dp[u]=1;
        else dp[u]=0;
    }
}

void dep_dfs(int u,int f,int d){
    ans=max(ans,d);
    for(auto v:G[u]){
        if(v==f)continue;
        dep_dfs(v,u,d+1);
    }
}

int main(){
    int n;cin>>n;
    for(int i=1;i<=n-1;i++){
        int u,v;scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dep_dfs(1,-1,0);
    dfs(1,-1,0);
    cout<<dp[1]<<endl;
}
