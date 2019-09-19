#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef unsigned long long ULL;
LL Gcd(LL a, LL b){if (b == 0) return a; return Gcd(b , a%b);}
LL Lcm(LL a, LL b){ return a/Gcd(a,b)*b;}
inline int read(){
    int f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 2e5 + 10;
struct node {
    int to,nex;
}ed[maxn << 1];
int head[maxn],tot;
int dep[maxn],pre[maxn],siz[maxn];
int vis[maxn],ismonster[maxn];
void add(int u,int v){
    ed[++tot] = (node){v,head[u]};
    head[u] = tot;
}
int find(int x){
    if (pre[x] == x) return x;
    return pre[x] = find(pre[x]);
}
void join(int x,int y){
    int fx = find(x),fy = find(y);
    if (fx != fy){
        pre[fx] = fy;
        siz[fy] += siz[fx];
    }
}
void dfs(int u,int fa,int s){
    if (vis[u] || ismonster[u]) return;
    vis[u] = 1;
    join(u,s);
    for(int i=head[u]; i; i=ed[i].nex){
        int v = ed[i].to;
        if (v != fa){
            dfs(v,u,s);
        }
    }
}
int main(){
    //freopen("/Users/chutong/ACM/data.in","r",stdin);
    //freopen("/Users/chutong/ACM/data.out","w",stdout);
    int T = read();
    while(T--){
        int n = read(),m = read(),k = read();
        tot = 0;
        memset(vis,0,sizeof (vis));
        memset(head,0,sizeof (head));
        memset(siz,0,sizeof(siz));
        memset(pre,0,sizeof(pre));
        memset(ismonster,0,sizeof(ismonster));
        memset(dep,0,sizeof(dep));
        for(int i=1; i<=n; i++) {
            pre[i] = i;
            siz[i] = 1;
        }
        for(int i=1; i<=m; i++){
            int u = read(),v = read();
            add(u,v);
            add(v,u);
            dep[u]++;
            dep[v]++;
        }
        for(int i=1; i<=k; i++){
            int c = read();
            ismonster[c] = 1;
            siz[c]--;
        }
        for(int i=1; i<=n; i++){
            if (!vis[i]) dfs(i,0,i);
        }
        double ans = 0;
        for(int i=1; i <= n; i++){
            int tag = 0,res = 0;
            if (ismonster[i]){
                for(int j=head[i]; j; j=ed[j].nex){
                    int vv = ed[j].to;
                    int fv = find(vv);
                    res += (siz[fv] + siz[find(1)]);
                    if (fv == find(1)){
                        res -= siz[find(1)];
                        tag = 1;
                    }
                }
            }
            //if (tag)cout << res << ' ' << i << ' ' << dep[i] << endl;
            if (tag) ans = max(ans,(double)res/(double)dep[i]);
        }
        printf("%.7f\n",ans);
    }
    return 0;
}
