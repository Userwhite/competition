#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
#define inf 0x3f3f3f3f
using namespace std;

const int maxn=2e6+100;
inline int read(){int num=0,w=0;char ch=0;while(!isdigit(ch)){w|=ch=='-';ch=getchar();}while(isdigit(ch))
{num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}return w? -num: num;}

inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9)write(x / 10);putchar(x % 10 + '0');}

struct tree2{
    tree2 *lson,*rson;
    int x;
}dizhi[maxn<<2],*root=&dizhi[0];

int n,m,t=1;
int lsh[maxn],cnt,mp[maxn];
struct node{
    int z,x;
}A[maxn];

inline void push_up(tree2 *tree,int l,int r){
    tree->x=tree->lson->x+tree->rson->x;
}

inline void build(tree2 *tree,int l,int r){
    if(l==r){
        tree->x=0;
        return ;
    }
    tree->lson=&dizhi[t++];
    tree->rson=&dizhi[t++];
    int mid=(l+r)>>1;
    build(tree->lson,l,mid);
    build(tree->rson,mid+1,r);
    push_up(tree,l,r);
}

inline void update(tree2 *tree,int l,int r,int x,int d){
    if(l==r){
        tree->x=d;
        return ;
    }
    int mid=(l+r)>>1;
    if(x<=mid)update(tree->lson,l,mid,x,d);
    else update(tree->rson,mid+1,r,x,d);
    push_up(tree,l,r);
}

inline int query(tree2 *tree,int l,int r,int x,int y){
    if(x<=l&&r<=y){
        int mid=(l+r)>>1;
        if(l==r){
            if(tree->x==0)return l;
            else return -1;
        }
        if(l<=mid&&tree->lson->x<mid-l+1)return query(tree->lson,l,mid,x,y);
        else if(mid+1<=r&&tree->rson->x<r-mid)return query(tree->rson,mid+1,r,x,y);
        return -1;
    }
    int mid=(l+r)>>1;
    int t=-1;
    if(x<=mid&&tree->lson->x<mid-l+1)t=query(tree->lson,l,mid,x,y);
    if(y>mid&&t==-1&&tree->rson->x<r-mid)t=query(tree->rson,mid+1,r,x,y);
    return t;
}

int main(){
    n = read();
    m = read();
    for(int i=1;i<=m;i++){
        A[i].z = read();
        A[i].x = read();
        lsh[2*i-1] = A[i].x;
        if(A[i].x<n)lsh[2*i]=A[i].x+1;
        else lsh[2*i]=A[i].x;
    }
    sort(lsh+1,lsh+1+2*m);
    cnt=unique(lsh+1,lsh+1+2*m)-lsh-1;
    int len = cnt;
    for(int i=1;i<=m;i++){
        A[i].x=lower_bound(lsh+1,lsh+1+cnt,A[i].x)-lsh;
    }
    for(int i=1;i<=cnt;i++){
        mp[i] = lsh[i];
    }
    build(root,1,len);
    for(int i=1;i<=m;i++){
        if(A[i].z==1){
            update(root,1,len,A[i].x,1);
        }else{
            int ret=query(root,1,len,A[i].x,len);
            if(ret==-1)putchar('-'),putchar('1'),putchar('\n');
            else write(mp[ret]),putchar('\n');
        }
    }
}
