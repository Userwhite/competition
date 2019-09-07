#include <set>
#include <map>
#include <queue>
#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
int Gcd(int a,int b){if (b == 0) return a; return Gcd(b , a%b);}
int Lcm(int a, int b){ return a/Gcd(a,b)*b;}
inline int read(){
    int f = 1, x = 0;char ch = getchar();
    while (ch > '9' || ch < '0'){if (ch == '-')f = -f;ch = getchar();}
    while (ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
const int maxn = 6e5 + 10;
struct Palindrome_Aho{
    int len[maxn],nex[maxn][26];
    int fail[maxn],s[maxn];
    LL cnt[maxn][26];
    int n,totNode,last,cur;
    LL ans,value[maxn],res[maxn];
    int newnode(int p){
        for(int i=0; i<26; i++) nex[totNode][i] = 0;
        value[totNode] = 0; 
        len[totNode] = p;
        return totNode++;
    }
    void init(){
        totNode = last = n = 0;
        newnode(0); newnode(-1);
        s[0] = -1;
        fail[0] = 1;
    }
    int Fail(int x){
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    void add(int ch){
        ch -= 'a';
        s[++n] = ch;
        cur = Fail(last);
        if (!nex[cur][ch]){
            int now = newnode(len[cur]+2);
            fail[now] = nex[Fail(fail[cur])][ch];
            nex[cur][ch] = now;
        }
        for(int i=0; i<26; i++){
            cnt[nex[cur][ch]][i] = cnt[cur][i];
        }
        cnt[nex[cur][ch]][ch]++;
        if (!value[nex[cur][ch]]){
            value[nex[cur][ch]] = value[cur];
            if (!cnt[cur][ch]) value[nex[cur][ch]]++;
        }
        last = nex[cur][ch];
        res[last]++;
    }
    void count(){
        for(int i=totNode-1; i>=0; i--){
            res[fail[i]] += res[i];
            //res[fail[i]] %= mod;
        }
        for(int i=totNode-1; i>=0; i--){
            ans = ans + value[i]*res[i];
        }
    }
}PTree;
int main(){
    PTree.init();
    string s;
    cin >> s;
    for(int i=0; i<s.length(); i++){
        PTree.add(s[i]);
    }
    PTree.count();
    cout << PTree.ans << endl;
    return 0;
}
