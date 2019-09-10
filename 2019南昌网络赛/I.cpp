#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e5+500;
const int limit = 2e5+50;

struct node{
    int t,pos,val,id;
    node(){}
    node(int _t,int _pos,int _val,int _id):t(_t),pos(_pos),val(_val),id(_id){}
    friend bool operator < (node a,node b){
        if(a.t==b.t&&a.pos==b.pos)return a.val<b.val;
        if(a.t==b.t)return a.pos<b.pos;
        return a.t<b.t;
    }
}q[maxn*20],tmp[maxn*20];

int A[maxn],C[200100],vis[maxn];
int n,m,ans[maxn];
int lowbit(int x){return (x&(-x));}
void change(int x,int d){for(int i=x;i<=limit;i+=lowbit(i)){C[i]+=d;}}
int query(int x){if(x==0)return 0;int ret=0;for(int i=x;i;i-=lowbit(i)){ret+=C[i];}return ret;}

int check(int now){
    if(A[now]==A[now-1]&&A[now]==A[now+1])return 1;
    if(A[now]==A[now-1])return 2;
    if(A[now]==A[now+1])return 3;
    return 4;
}

void cdq(int l,int r){
    if(l>=r)return ;
    int mid=(l+r)>>1;
    cdq(l,mid);cdq(mid+1,r);
    int num=l-1,i,j;
    for(i=l,j=mid+1;i<=mid&&j<=r;){
        if(q[i].pos<=q[j].pos){
            if(!vis[abs(q[i].id)]){
                if(q[i].id>0)change(q[i].val,1);
                else change(q[i].val,-1);
            }
            tmp[++num]=q[i++];
        }
        else{
            if(vis[abs(q[j].id)]){
                if(q[j].id>0)ans[q[j].id]+=query(q[j].val);
                else ans[-q[j].id]-=query(q[j].val);
            }
            tmp[++num]=q[j++];
        }
    }
    while(i<=mid){
        if(!vis[abs(q[i].id)]){
            if(q[i].id>0)change(q[i].val,1);
            else change(q[i].val,-1);
        }
        tmp[++num]=q[i++];
    }
    while(j<=r){
        if(vis[abs(q[j].id)]){
            if(q[j].id>0)ans[q[j].id]+=query(q[j].val);
            else ans[-q[j].id]-=query(q[j].val);
        }
        tmp[++num]=q[j++];
    }
    for(int k=l;k<=mid;k++){
        if(!vis[abs(q[k].id)]){
            if(q[k].id>0)change(q[k].val,-1);
            else change(q[k].val,1);
        }
    }
    for(int k=l;k<=r;k++)q[k]=tmp[k];
}

int main(){
    cin>>n>>m;n++;
    A[1]=A[n+1]=-1;
    for(int i=1;i<=n-1;i++)scanf("%d",&A[i+1]),A[i+1]++;
    int cnt=0;
    for(int i=2;i<=n;i++){
        if(A[i]==A[i-1])continue;
        q[++cnt]=node(0,i,A[i],m+10);
        vis[m+10]=0;
    }
    for(int i=1;i<=m;i++){
        int op;scanf("%d",&op);
        if(op==1){
            int pos,val,last;
            scanf("%d%d",&pos,&val);
            pos++,val++;
            vis[i]=0;
            if(A[pos]==val)continue;
            int pre=check(pos);
            last=A[pos],A[pos]=val;
            int now=check(pos);
            if(pre==1){
                q[++cnt]=node(i,pos,val,i);
                q[++cnt]=node{i,pos+1,A[pos+1],i};
            }
            if(pre==2){
                q[++cnt]=node(i,pos,val,i);
                if(now==3){
                    q[++cnt]=node(i,pos+1,A[pos+1],-i);
                }
            }
            if(pre==3){
                q[++cnt]=node(i,pos+1,A[pos+1],i);
                if(now==2){
                    q[++cnt]=node(i,pos,last,-i);
                }
                else{
                    q[++cnt]=node(i,pos,last,-i);
                    q[++cnt]=node(i,pos,val,i);
                }
            }
            if(pre==4){
                if(now==1){
                    q[++cnt]=node(i,pos,last,-i);
                    q[++cnt]=node(i,pos+1,A[pos+1],-i);
                }
                if(now==2){
                    q[++cnt]=node(i,pos,last,-i);
                }
                if(now==3){
                    q[++cnt]=node(i,pos,last,-i);
                    q[++cnt]=node(i,pos,val,i);
                    q[++cnt]=node(i,pos+1,A[pos+1],-i);
                }
                if(now==4){
                    q[++cnt]=node(i,pos,last,-i);
                    q[++cnt]=node(i,pos,val,i);
                }
            }
        }
        else{
            int l,r,x,y;
            scanf("%d%d%d%d",&l,&r,&x,&y);
            l+=2,r++,x++,y++;
            if(A[l-1]>=x&&A[l-1]<=y)ans[i]=1;
            else ans[i]=0;
            vis[i]=1;
            q[++cnt]=node(i,r,y,i);
            q[++cnt]=node(i,l-1,y,-i);
            q[++cnt]=node(i,r,x-1,-i);
            q[++cnt]=node(i,l-1,x-1,i);
        }
    }
    sort(q+1,q+1+cnt);
    cdq(1,cnt);
    for(int i=1;i<=m;i++)if(vis[i]){
        printf("%d\n",ans[i]);
    }
}
