#include<bits/stdc++.h>
#define FOR(i,l,r) for(int i=l;i<=r;i++)
using namespace std;

typedef long long ll;
const int maxn = 2e5+200;

int n;

struct node{
    string str;
    int val1,val2,val3,id;
    int a[8];
    friend bool operator < (node a,node b){
        if(a.id!=b.id)return a.id<b.id;
        if(a.id==1){
            return a.str<b.str;
        }
        if(a.id==2||a.id==8){
            if(a.val1==b.val1)return a.str<b.str;
            return a.val1>b.val1;
        }
        if(a.id==3||a.id==4||a.id==5||a.id==7){
            if(a.val1==b.val1&&a.val2==b.val2)return a.str<b.str;
            if(a.val1==b.val1)return a.val2>b.val2;
            return a.val1>b.val1;
        }
        if(a.id==6){
            if(a.val1==b.val1&&a.val2==b.val2&&a.val3==b.val3)return a.str<b.str;
            if(a.val1==b.val1&&a.val2==b.val2)return a.val3>b.val3;
            if(a.val1==b.val1)return a.val2>b.val2;
            return a.val1>b.val1;
        }
    }
}A[maxn];

int get_type(node& tmp){
    if(tmp.a[0]==1&&tmp.a[1]==10&&tmp.a[2]==11&&tmp.a[3]==12&&tmp.a[4]==13)return 1;
    if(tmp.a[1]==tmp.a[0]+1&&tmp.a[2]==tmp.a[0]+2&&tmp.a[3]==tmp.a[0]+3&&tmp.a[4]==tmp.a[0]+4){
        tmp.val1=tmp.a[4];
        return 2;
    }
    if(tmp.a[2]==tmp.a[1]&&tmp.a[3]==tmp.a[1]&&tmp.a[4]==tmp.a[1]){
        tmp.val1=tmp.a[1],tmp.val2=tmp.a[0];
        return 3;
    }
    if(tmp.a[1]==tmp.a[0]&&tmp.a[2]==tmp.a[0]&&tmp.a[3]==tmp.a[0]){
        tmp.val1=tmp.a[0],tmp.val2=tmp.a[4];
        return 3;
    }
    if(tmp.a[0]==tmp.a[1]&&tmp.a[3]==tmp.a[2]&&tmp.a[4]==tmp.a[2]){
        tmp.val1=tmp.a[4],tmp.val2=tmp.a[1];
        return 4;
    }
    if(tmp.a[1]==tmp.a[0]&&tmp.a[2]==tmp.a[0]&&tmp.a[4]==tmp.a[3]){
        tmp.val1=tmp.a[0],tmp.val2=tmp.a[4];
        return 4;
    }
    if(tmp.a[1]==tmp.a[0]&&tmp.a[2]==tmp.a[0]){
        tmp.val1=tmp.a[2],tmp.val2=tmp.a[3]+tmp.a[4];
        return 5;
    }
    if(tmp.a[2]==tmp.a[1]&&tmp.a[3]==tmp.a[1]){
        tmp.val1=tmp.a[3],tmp.val2=tmp.a[0]+tmp.a[4];
        return 5;
    }
    if(tmp.a[3]==tmp.a[2]&&tmp.a[4]==tmp.a[2]){
        tmp.val1=tmp.a[4],tmp.val2=tmp.a[0]+tmp.a[1];
        return 5;
    }
    if(tmp.a[1]==tmp.a[2]){
        if(tmp.a[3]==tmp.a[4]){
            tmp.val1=tmp.a[4],tmp.val2=tmp.a[2];
            tmp.val3=tmp.a[0];
            return 6;
        }
    }
    if(tmp.a[0]==tmp.a[1]){
        if(tmp.a[3]==tmp.a[4]){
            tmp.val1=tmp.a[4],tmp.val2=tmp.a[1];
            tmp.val3=tmp.a[2];
            return 6;
        }
    }
    if(tmp.a[0]==tmp.a[1]){
        if(tmp.a[2]==tmp.a[3]){
            tmp.val1=tmp.a[3],tmp.val2=tmp.a[1];
            tmp.val3=tmp.a[4];
            return 6;
        }
    }
    int sum=0;
    for(int i=0;i<5;i++){
        sum+=tmp.a[i];
    }
    for(int i=1;i<5;i++){
        if(tmp.a[i]==tmp.a[i-1]){
            tmp.val1=tmp.a[i],tmp.val2=sum-2*tmp.a[i];
            return 7;
        }
    }
    tmp.val1=sum;
    return 8;
}

int main(){
    while(~scanf("%d",&n)){
        for(int i=1;i<=n;i++){
            string cards;
            cin>>A[i].str>>cards;
            int pos=0,sz=cards.size(),cnt=-1;
            while(pos<sz){
                if(cards[pos]=='1'){
                    pos++;
                    A[i].a[++cnt]=10;
                }
                else if(cards[pos]>='0'&&cards[pos]<='9')A[i].a[++cnt]=cards[pos]-'0';
                else{
                    if(cards[pos]=='A')A[i].a[++cnt]=1;
                    if(cards[pos]=='J')A[i].a[++cnt]=11;
                    if(cards[pos]=='Q')A[i].a[++cnt]=12;
                    if(cards[pos]=='K')A[i].a[++cnt]=13;
                }
                pos++;
            }
            sort(A[i].a,A[i].a+5);
            A[i].id=get_type(A[i]);
        }
        sort(A+1,A+1+n);
        for(int i=1;i<=n;i++)cout<<A[i].str<<endl;
    }
}
