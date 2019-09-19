#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long LL;
typedef unsigned long long ULL;
LL Gcd(LL a, LL b){if (b == 0) return a; return Gcd(b , a%b);}
LL Lcm(LL a, LL b){ return a/Gcd(a,b)*b;}
inline int read(){
	int f = 1, x = 0;char ch = getchar();
	while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
	while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}
const int maxn = 1e6 + 10;
LL sum[maxn][11];
int b[11] = {2,3,4,5,6,7,8,9,10};
int main(){
	//freopen("/Users/chutong/ACM/data.in","r",stdin);
	//freopen("/Users/chutong/ACM/data.out","w",stdout);
	for(int i=1; i<maxn; i++){
		for(int j=0; j<9; j++){
			sum[i][b[j]] = sum[i-1][b[j]];
			int tmp = i;
			while(tmp){
				sum[i][b[j]] += tmp % b[j];
				tmp /= b[j];
			}
		}
	}		 	
	int T = read(),kase = 1;
	while(T--){
		int n = read(),b = read();
		printf("Case #%d: %lld\n",kase++,sum[n][b]);
	}
	return 0;
}
