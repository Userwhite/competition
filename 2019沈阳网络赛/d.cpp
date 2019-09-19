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
#define int long long
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
LL Gcd(LL a,LL b){if (b == 0) return a; return Gcd(b , a%b);}
int Lcm(int a, int b){ return a/Gcd(a,b)*b;}
inline int read(){
    int f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
const LL maxn = 2e5 + 10;
const LL mod = 1e9 + 7;
LL siz[maxn],maxp[maxn],vis[maxn];
int dis[maxn];
int n,m,sum,root;
struct node{ int to,nex; LL w; }ed[maxn << 1];
int head[maxn],tot;
LL cnt[3],res[3];
void add(int u,int v,LL w){
    ed[tot] = (node){v,head[u],w};
    head[u] = tot++;
}
void getrt(int u,int fa){
    siz[u] = 1; maxp[u] = 0;
    for(int i=head[u]; ~i; i=ed[i].nex){
        int v = ed[i].to;
        if (vis[v] || v == fa) continue;
        getrt(v,u);
        siz[u] += siz[v];
        maxp[u] = max(maxp[u],siz[v]);
    }
    maxp[u] = max(maxp[u],sum-siz[u]);
    if (maxp[u] < maxp[root]) root = u;
}
void getdis(int u,int fa){
    cnt[dis[u] % 3]++;
    res[dis[u] % 3] += dis[u];
    for(int i=head[u]; ~i; i=ed[i].nex){
        int v = ed[i].to;
        if (vis[v] || v == fa) continue;
        dis[v] = (dis[u] + ed[i].w);
        getdis(v,u);
    }
}
LL ans[3] = {0,0,0};
LL calc(int u,int w,int tag){
    memset(cnt,0,sizeof(cnt));
    memset(res,0,sizeof(res));
    dis[u] = w;
    getdis(u,0);
    if (tag == 1) {
        ans[0] += (res[1]*cnt[2] % mod + res[2]*cnt[1] % mod + res[0]*cnt[0] % mod) % mod;
        ans[1] += (res[1]*cnt[0] % mod + res[2]*cnt[2] % mod + res[0]*cnt[1] % mod) % mod;
        ans[2] += (res[1]*cnt[1] % mod + res[2]*cnt[0] % mod + res[0]*cnt[2] % mod) % mod;
    }else{
        ans[0] -= (res[1]*cnt[2] % mod + res[2]*cnt[1] % mod + res[0]*cnt[0] % mod) % mod;
        ans[1] -= (res[1]*cnt[0] % mod + res[2]*cnt[2] % mod + res[0]*cnt[1] % mod) % mod;
        ans[2] -= (res[1]*cnt[1] % mod + res[2]*cnt[0] % mod + res[0]*cnt[2] % mod) % mod;
        ans[0] = (ans[0] + mod) % mod;
        ans[1] = (ans[1] + mod) % mod;
        ans[2] = (ans[2] + mod) % mod;
    }
}
void solve(int u){
    calc(u,0,1);
    vis[u] = 1;
    for(int i=head[u]; ~i; i=ed[i].nex){
        int v = ed[i].to;
        if (vis[v]) continue;
        calc(v,ed[i].w,0);
        root = 0;
        sum = siz[v];
        getrt(v,0);
        solve(root);
    }
}
signed main(){
    LL n;
    while(scanf("%d",&n) == 1){
        ans[0] = ans[1] = ans[2] = 0;
        root = tot = sum = 0;
        memset(dis,0,sizeof(dis));
        memset(vis,0,sizeof(vis));
        memset(maxp,0,sizeof(maxp));
        memset(siz,0,sizeof(siz));
        memset(head,-1,sizeof(head));
        for(int i=1; i<n; i++){
            int x = read(),y = read(),w = read();
            x++; y++;
            add(x,y,w);
            add(y,x,w);
        }
        LL tot = n*n;
        sum = maxp[0] = n;
        root = 0;
        getrt(1,0);
        solve(root);
        cout << ans[0]*2%mod << ' ' << ans[1]*2%mod << ' ' << ans[2]*2%mod << endl;
    }   
    return 0;
}
//   ans[1] += cnt[1]*cnt[0]*2 + cnt[2]*cnt[2];
        // ans[2] += cnt[0]*cnt[2]*2 + cnt[1]*cnt[1];
