#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef long long ll;
const int maxn = 1e6+200;
inline int read(){int num=0,w=0;char ch=0;while(!isdigit(ch)){w|=ch=='-';ch=getchar();}while(isdigit(ch))
{num=(num<<3)+(num<<1)+(ch^48);ch=getchar();}return w? -num: num;}

inline void write(int x){if(x<0){putchar('-');x=-x;}if(x>9)write(x / 10);putchar(x % 10 + '0');}

int A[maxn];
int B[maxn];
vector<pair<int,int> >Q;

int main(){
    int T;cin>>T;
    int kase=0;
    while(T--){
        int n,m;
        n=read(),m=read();
        Q.clear();
        for(int i=1;i<=m;i++){
            int l=read(),r=read();
            Q.push_back(make_pair(l,0));
            Q.push_back(make_pair(r+1,1));
        }
        sort(Q.begin(),Q.end());
        Q.push_back(make_pair(n-1,0));
        int sum=0,now=0;
        for(int i=0;i<int(Q.size())-1;i++){
            now^=1;
            int pre=Q[i].first;
            while(i+1<int(Q.size())-1&&Q[i+1].first==pre){
                i++;
                now^=1;
            }
            if(now)sum+=Q[i+1].first-Q[i].first;
        }
        printf("Case #%d: %d\n",++kase,sum);
    }
}
