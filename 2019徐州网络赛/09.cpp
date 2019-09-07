#include<bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;
int cnt,n,m,pos[maxn],ans[maxn];

struct node{
    int l,r,id;
    void get(){
        if(l>r)swap(l,r);
    }
    friend bool operator < (node a,node b){
        if(a.l==b.l&&a.r==b.r)return a.id<b.id;
        if(a.l!=b.l)return a.l>b.l;
        return a.r<b.r;
    }
}A[maxn*20];

void init(){
    for(int i=1;i<=n;i++){
        for(int j=2*i;j<=n;j+=i){
            A[++cnt]=node{pos[i],pos[j],0};
            A[cnt].get();
        }
    }
}

int C[100005];
const int limit=100003;
int lowbit(int x){return (x&(-x));}
void change(int x,int d){for(int i=x;i<=limit;i+=lowbit(i)){C[i]+=d;}}
int query(int x){if(x==0)return 0;int ret=0;for(int i=x;i;i-=lowbit(i)){ret+=C[i];}return ret;}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        pos[x]=i;
    }
    init();
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        A[++cnt].l=x,A[cnt].r=y,A[cnt].id=i;
    }
    sort(A+1,A+1+cnt);
    for(int i=1;i<=cnt;i++){
        if(A[i].id){
            ans[A[i].id]=query(A[i].r);
        }
        else{
            change(A[i].r,1);
        }
    }
    for(int i=1;i<=m;i++)printf("%d\n",ans[i]);
}
