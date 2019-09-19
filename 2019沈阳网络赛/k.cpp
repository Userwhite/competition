#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<string.h>
#include<math.h>
#define int long long
#define ll long long
#define LL long long
using namespace std;
const int mod = 1E9+7,MOD=1E9+7;
const int MAXN = 80;
const int N=100,M=100;
int a[MAXN][MAXN];//增广矩阵
int x[MAXN];//解集
int f[MAXN];
bool free_x[MAXN];//标记是否是不确定的变元
inline int read(){
    char c=getchar();int x=0,f=1;while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}return x*f;}
int gcd(int a,int b)
{
    while(b)
    {
        int t = b;
        b = a%b;
        a = t;
    }
    return a;
}

int lcm(int a,int b)
{
    return a/gcd(a,b)*b;
}

LL inv(LL a,LL m)
{
    if(a == 1) return 1;
    return inv(m%a,m)*(m-m/a)%m;
}

int Gauss(int equ,int var)
{
    int max_r,col,k;

    for(k = 0, col = 0; k < equ && col < var; ++k,++col)
    {
        max_r = k;
        for(int i = k+1; i < equ; ++i)
            if(abs(a[i][col]) > abs(a[max_r][col]))
                max_r = i;
        if(a[max_r][col] == 0)
        {
            --k;
            continue;
        }
        if(max_r != k)
            for(int j = col; j < var+1; ++j)
                swap(a[k][j],a[max_r][j]);
        for(int i = k+1; i < equ; ++i)
        {
            if(a[i][col] != 0)
            {
                int LCM = lcm(abs(a[i][col]),abs(a[k][col]));
                int ta = LCM/abs(a[i][col]);
                int tb = LCM/abs(a[k][col]);
                if(a[i][col]*a[k][col] < 0) tb = -tb;
                for(int j = col; j < var+1; ++j)
                    a[i][j] = ((a[i][j]*ta-a[k][j]*tb)%mod+mod)%mod;
            }
        }
    }
    for(int i = k; i < equ; ++i)
        if(a[i][col] != 0) 
        {
    //        printf("a[%d][%d] %d\n",i,col,a[i][col]);
            return -1;//无解
        }
    if(k < var) return var-k;//多解
    for(int i = var-1; i >= 0; --i)
    {
        int temp = a[i][var];
        for(int j = i+1; j < var; ++j)
        {
            if(a[i][j] != 0)
            {
                temp -= a[i][j]*x[j];
                temp = (temp%mod+mod)%mod;
            }
        }
        x[i] = (temp*inv(a[i][i],mod))%mod;
    }
    return 0;
}
struct Matrix
{
    ll A[N][N];
    int len;
    Matrix(){
        memset(A,0,sizeof(A));
        len = 100;
    }
    Matrix(int lens):len(lens){
        memset(A,0,sizeof(A));
    }
    void einit() {
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
                A[i][j] = (i==j);
    }
    void Creat(int lens)
    {
        len = lens;
        if(len > N) exit(1);
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
            scanf("%lld",&A[i][j]);
    }
    void output()
    {
        for(int i=0;i<len;i++)
        {
            for(int j=0;j<len-1;j++)
                printf("%lld ",A[i][j]);
            printf("%lld\n",A[i][len-1]);
        }
    }
    Matrix operator * (const Matrix &a){
        Matrix ans(len);
        for(int k=0;k<len;k++)
        {
            for(int i=0;i<len;i++) if(A[i][k])
            {
                ll temp;
                for(int j=0;j<len;j++) if(a.A[k][j])
                {
                    temp = (A[i][k]*a.A[k][j]) % mod;
                    ans.A[i][j] = (ans.A[i][j] + temp) % mod;
                    ans.A[i][j]=(ans.A[i][j]+mod)%mod;
                }
            }
        }
        return ans;
    }
    Matrix operator ^ (const ll &b) const { /// 注意运算符号顺序
        Matrix ans(len),a = (*this);ans.einit();
        ll t = b;
        while(t) {
            if(t & 1) ans = ans * a;
            a = a * a;
            t >>= 1;
        }
        return ans;
    }
    void operator = (const Matrix &a){
        len = a.len;
        for(int i=0;i<len;i++)
            for(int j=0;j<len;j++)
            A[i][j] = a.A[i][j];
    }
}base,ans,tmp;
int add(int x,int y) {x+=y;if(x>mod)x-=mod;return x;} 
int sub(int x,int y) {x-=y;if(x<0)x+=mod;return x;} 
void pre(int k)
{
	memset(ans.A,0,sizeof(ans.A));
	memset(base.A,0,sizeof(base.A));
	for(int i=0;i<k;i++) ans.A[0][0]=(ans.A[0][0]+f[i])%mod;
	for(int i=k;i>=1;i--) 
	ans.A[0][k-i+1]=f[i-1];
	
	base.A[0][0]=1;
	for(int i=1;i<k+1;i++) base.A[i][0]=base.A[i][1]=x[i-1];
	for(int i=2;i<k+1;i++) base.A[i-1][i]=1;
}
signed main()
{
    int i,j;
    int equ,var,k,n,t;
    t=read();
    while(t--)
    {
    	k=read();n=read();
        memset(a,0,sizeof(a));
        equ=var=k;
        for(int i=0;i<2*k;i++) f[i]=read();
        for(int i=0;i<equ;i++)
        {
        	for(int j=0;j<var+1;j++)
            a[i][j]=f[j+i];
        }
        Gauss(equ,var);
        reverse(x,x+k);
		//for(int i=0;i<var;i++) printf("%lld\n",x[i]); 
		pre(k);
		if(n<=k)
		{
			int sum=0;
			for(int i=0;i<n;i++) sum+=f[i];
			printf("%lld\n",sum);
			continue;
		}
		ans=ans*(base^(n-k));
		printf("%lld\n",ans.A[0][0]);
    }
    return 0;
}
/*
1
2 5
4 8 6 7
*/
