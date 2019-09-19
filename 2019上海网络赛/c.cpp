#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define ll long long
using namespace std;
const int maxn=1E6+100;
inline int read()
{
	char c=getchar();int x=0,f=1;
	while(c<'0'||c>'9') {if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
const double Pi=acos(-1.0);
struct complex
{
	double x,y;
	complex(double a=0,double b=0){x=a,y=b;} 
}A[maxn],B[maxn];
complex operator+(complex a,complex b){return complex(a.x+b.x,a.y+b.y);}
complex operator-(complex a,complex b){return complex(a.x-b.x,a.y-b.y);}
complex operator*(complex a,complex b){return complex(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
int r[maxn],lim=1,l=0;
void FFT(complex *A,int type)
{
    for(int i=0;i<lim;i++) 
        if(i<r[i]) swap(A[i],A[r[i]]);//求出要迭代的序列 
    for(int mid=1;mid<lim;mid<<=1)//待合并区间的中点
    {
        complex Wn( cos(Pi/mid) , type*sin(Pi/mid) ); //单位根 
        for(int R=mid<<1,j=0;j<lim;j+=R)//R是区间的右端点，j表示前已经到哪个位置了 
        {
            complex w(1,0);//幂 
            for(int k=0;k<mid;k++,w=w*Wn)//枚举左半部分 
            {
                 complex x=A[j+k],y=w*A[j+mid+k];//蝴蝶效应 
                A[j+k]=x+y;
                A[j+mid+k]=x-y;
            }
        }
    }
}
void pre(int len)
{
	lim=1;l=0;
	while(lim<len) lim<<=1,l++;
    for(int i=0;i<lim;i++) r[i]= ( r[i>>1]>>1 )| ( (i&1)<<(l-1) ) ;
}
int t,n,a[3][100050];
ll num1[maxn],num2[maxn];
ll sum[maxn];
ll work(int id)
{
	ll ans=0;
	int id1=(id+1)%3,id2=(id+2)%3,mx=0;
	for(int i=0;i<n;i++)
	{
		mx=max(mx,max(a[id1][i],a[id2][i])+1);
		num1[a[id1][i]]++;num2[a[id2][i]]++;
	}
	lim=1,l=0;
	pre(mx+mx);
	for(int i=0;i<mx;i++)
	{
		A[i]=complex(num1[i],0);
		B[i]=complex(num2[i],0);
		num1[i]=num2[i]=0;
	}
	for(int i=mx;i<lim;i++) A[i]=B[i]=complex(0,0);
	FFT(A,1);FFT(B,1);
	for(int i=0;i<lim;i++) A[i]=A[i]*B[i];
	FFT(A,-1);
	for(int i=0;i<=lim;i++) sum[i]=0;
	for(int i=0;i<lim;i++) sum[i]=(ll)(A[i].x/lim+0.5);
	//for(int i=1;i<lim;i++) cout<<sum[i]<<" ";
	//cout<<endl;
	for(int i=1;i<=lim;i++) sum[i]+=sum[i-1];
	for(int i=0;i<n;i++)
	{
		ans+=sum[lim]-sum[a[id][i]-1];
	}
	return ans;
}
struct qw
{
	int id,len;
	qw(){}
	qw(int a,int b){id=a;len=b;}
	bool operator<(const qw &x)const
	{
		return len<x.len;
	} 
}v[300050];
ll solve()
{
	ll ans=0;
	ans+=work(0);
	ans+=work(1);
	ans+=work(2);
	int tot=0,cnt[3];
	for(int i=0;i<n;i++) v[i]=qw(0,a[0][i]);
	for(int i=n;i<2*n;i++) v[i]=qw(1,a[1][i-n]);
	for(int i=2*n;i<3*n;i++) v[i]=qw(2,a[2][i-2*n]);
	sort(v,v+3*n);
	cnt[0]=cnt[1]=cnt[2]=0;
	for(int i=0;i<3*n;i++)
	{
		int id=v[i].id;
		int id1=(id+1)%3,id2=(id+2)%3;
		ans-=(ll)(n-cnt[id1])*cnt[id2];
		ans-=(ll)(n-cnt[id2])*cnt[id1];
		ans-=(ll)(n-cnt[id2])*(n-cnt[id1]);
		cnt[id]++;
	}
	return ans;
}
ll baoli()
{
	int tot=0,cnt[3];ll ans=0;
	sort(a[0],a[0]+n);
	sort(a[1],a[1]+n);
	sort(a[2],a[2]+n);
	for(int i=0;i<n;i++) v[i]=qw(0,a[0][i]);
	for(int i=n;i<2*n;i++) v[i]=qw(1,a[1][i-n]);
	for(int i=2*n;i<3*n;i++) v[i]=qw(2,a[2][i-2*n]);
	sort(v,v+3*n);
	cnt[0]=cnt[1]=cnt[2]=0;
	for(int i=0;i<3*n;i++)
	{
		int id=v[i].id;
		int id1=(id+1)%3,id2=(id+2)%3;
		int tmp=cnt[id2];
		for(int j=0;j<cnt[id1];j++)
		{
			while(tmp&&a[id1][j]+a[id2][tmp-1]>=v[i].len) tmp--;
			ans+=cnt[id2]-tmp;
		}
		//cout<<ans<<endl;
		cnt[id]++;
	}
	return ans;
}
int main()
{
	//freopen("input.in","r",stdin);
	//freopen("test.out","w",stdout);
	t=read();int num=0;
	while(t--)
	{
		n=read();
		for(int i=0;i<n;i++) a[0][i]=read();
		for(int i=0;i<n;i++) a[1][i]=read();
		for(int i=0;i<n;i++) a[2][i]=read();
		ll ans;
		if(n<=2000) ans=baoli();
		else ans=solve();
		printf("Case #%d: %lld\n",++num,ans);
	}
}
