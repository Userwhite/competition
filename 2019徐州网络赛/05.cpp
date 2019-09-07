#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define inf 0x3f3f3f3f
using namespace std;

const int maxn=1e6+100;

struct tree2{
    tree2 *lson,*rson;
    int x,lazy;
}dizhi[maxn<<2],*root=&dizhi[0];

int n,m,t=1;
int lsh[maxn],num[maxn],cnt,g[maxn],to[maxn];

void push_up(tree2 *tree,int l,int r){
    tree->x=max(tree->lson->x,tree->rson->x);
}

void push_down(tree2 *tree,int l,int r){
    if(!tree->lazy)return ;
    tree->lson->x+=tree->lazy;
    tree->rson->x+=tree->lazy;
    tree->lson->lazy+=tree->lazy;
    tree->rson->lazy+=tree->lazy;
    tree->lazy=0;
}

void build(tree2 *tree,int l,int r){
    if(l==r){
        tree->x=to[l];
        return ;
    }
    tree->lson=&dizhi[t++];
    tree->rson=&dizhi[t++];
    int mid=(l+r)>>1;
    build(tree->lson,l,mid);
    build(tree->rson,mid+1,r);
    push_up(tree,l,r);
}

void update(tree2 *tree,int l,int r,int x,int y,int d){
    if(x<=l&&r<=y){
        tree->x+=d;
        tree->lazy+=d;
        return ;
    }
    push_down(tree,l,r);
    int mid=(l+r)>>1;
    if(x<=mid)update(tree->lson,l,mid,x,y,d);
    if(y>mid)update(tree->rson,mid+1,r,x,y,d);
    push_up(tree,l,r);
}

int query(tree2 *tree,int l,int r,int x,int y){
    if(x<=l&&r<=y){
        return tree->x;
    }
    push_down(tree,l,r);
    int mid=(l+r)>>1;
    int t1=-1,t2=-1;
    if(x<=mid)t1=query(tree->lson,l,mid,x,y);
    if(y>mid)t2=query(tree->rson,mid+1,r,x,y);
    return max(t1,t2);
}

inline int read(){int num=0,w=0;char ch=0;while(!isdigit(ch)){w|=ch=='-';ch=getchar();}while(isdigit(ch))
{num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}return w? -num: num;}

inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9)write(x / 10);putchar(x % 10 + '0');}

int main(){
    int n=read(),m=read();
    for(int i=1;i<=n;i++){
        num[i]=lsh[2*i-1]=read();
        lsh[2*i]=lsh[2*i-1]+m;
    }
    sort(lsh+1,lsh+1+2*n);
    cnt=unique(lsh+1,lsh+1+2*n)-lsh-1;
    for(int i=1;i<=n;i++){
        g[i]=lower_bound(lsh+1,lsh+1+cnt,num[i]+m)-lsh;
        num[i]=lower_bound(lsh+1,lsh+1+cnt,num[i])-lsh;
        to[num[i]]=i;
    }
    build(root,1,cnt);
    for(int i=1;i<=n;i++){
        update(root,1,cnt,1,cnt,-i-1);
        int tmp=query(root,1,cnt,g[i],cnt);
        update(root,1,cnt,1,cnt,i+1);
        if(tmp>=0)printf("%d",tmp);
        else printf("-1");
        if(i<n)putchar(' ');
    }
}
