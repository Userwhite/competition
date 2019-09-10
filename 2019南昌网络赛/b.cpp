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
using namespace std;
typedef long long LL;
typedef pair<LL,int> pi;
const int maxn = 1e5+10;
const int maxx = 2500000;
struct node {
    int to,nex;
    LL w;
}edge[maxx];
int head[maxn],vis[maxn];
LL dis1[maxn],dis2[maxn];
LL cnt,n,m,u,v,w,s,k,c;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}
void add(int u,int v,int w){
    edge[cnt] = (node){v,head[u],w};
    head[u] = cnt++;
}
void dijkstra(int s,LL dis[]){
    memset(vis,0,sizeof(vis));
    priority_queue<pi,vector<pi>,greater<pi> > pq;
    for(int i=0;i<=n;i++) dis[i] = LLONG_MAX; dis[s] = 0;
    pq.push(pi(0,s));
    while (!pq.empty()) {
        pi now = pq.top();pq.pop();
        int u = now.second;
        if (vis[u]) continue;
        else vis[u] = 1;
        for (int i=head[u]; ~i; i=edge[i].nex) {
            int v = edge[i].to;
            if (dis[v] > dis[u] + edge[i].w){
                dis[v] = dis[u] + edge[i].w;
                pq.push(pi(dis[v],v));
            }
        }
    }
}
int sp[maxn];
int main(){
    int T = read();
    while(T--){
        memset(head,-1,sizeof(head));
        memset(dis1,0,sizeof(dis1));
        memset(dis2,0,sizeof(dis2));
        n = read(),m = read(),s = read(),k = read(),c = read();
        int ss = n+1;
        for(int i=1; i<=k; i++) {
            sp[i] = read();
        }
        for(int i=1; i<=m; i++){
            LL u = read(),v = read(),w = read();
            add(u, v, w);
            add(v, u, w);
        }
        dijkstra(s,dis1);
        for(int i=1; i<=k; i++){
            add(ss,sp[i],0);
            add(sp[i],ss,0);
        }
        dijkstra(ss,dis2);
        LL val1 = 0,val2 = 0;
        for(int i=1; i<=n; i++){
            val1 = max(val1,dis1[i]);
            val2 = max(val2,dis2[i]);
        }
        if (val1 <= val2*c){
            printf("%lld\n",val1);
        }else{
            printf("%lld\n",val2);
        }
    }
    return 0;
}
