#include<bits/stdc++.h>
using namespace std;

__int128 n,m,dp[35][35];
int read(){
	int f=1,g=0;
	char ch=getchar();
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') ch=-1;
	for (;isdigit(ch);ch=getchar()) g=g*10+ch-'0';
	return f*g;
}
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}

int main(){
    int T;cin>>T;
    for(int i=0;i<=30;i++)dp[0][i]=1;
    for(int i=1;i<=30;i++){
        for(int j=0;j<=30;j++){
            dp[i][j]=dp[i-1][j]*j+dp[i-1][j+1];
        }
    }
    for(int kase=1;kase<=T;kase++){
        read(n),read(m);
        int t=0;
        printf("Case #%d: ",kase);
        for(int i=1;i<=n;i++){
            int pos=0;
            while(pos<t&&m>dp[n-i][t]){
                pos++;
                m-=dp[n-i][t];
            }
            printf("%c",'A'+pos);
            t=max(t,pos+1);
        }
        puts("");
    }
}
