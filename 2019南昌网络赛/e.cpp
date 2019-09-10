#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define inf 0x3f3f3f3f
using namespace std;

typedef long long ll;
const int maxn=4e7+10;

int lst[maxn],rst[maxn];
int vis[maxn];

void del(int x){
    lst[rst[x]]=lst[x];
    rst[lst[x]]=rst[x];
}

int main(){
    int T;cin>>T;
    while(T--){
        int n,m;scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++){
            if(i==1)lst[i]=n;
            else lst[i]=i-1;
            if(i==n)rst[i]=1;
            else rst[i]=i+1;
        }
        int now=1,tmp;
        for(int i=1;i<=n;i++){
            vis[now]=i;
            tmp=now;
            now=rst[now];
            del(tmp);
            for(int j=1;j<=m;j++){
                now=rst[now];
            }
        }
        int q;scanf("%d",&q);
        for(int i=1;i<=q;i++){
            int x;scanf("%d",&x);
            printf("%d\n",vis[x]);
        }
    }
}
