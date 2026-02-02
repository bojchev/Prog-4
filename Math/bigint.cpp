#include <bits/stdc++.h>
using namespace std;

class BigInt{
public:
    string s;

    BigInt(string x="0"){
        int k=0;
        while(k+1<x.size() && x[k]=='0') k++;
        s=x.substr(k);
    }

    bool lessThan(BigInt b){
        if(s.size()!=b.s.size()) return s.size()<b.s.size();
        return s<b.s;
    }

    BigInt operator+(BigInt b){
        string r="";
        int i=s.size()-1,j=b.s.size()-1,c=0;
        while(i>=0||j>=0||c){
            int a=0,d=0;
            if(i>=0) a=s[i--]-'0';
            if(j>=0) d=b.s[j--]-'0';
            int sm=a+d+c;
            r.push_back(char(sm%10+'0'));
            c=sm/10;
        }
        reverse(r.begin(),r.end());
        return BigInt(r);
    }

    BigInt operator-(BigInt b){
        string r="";
        int i=s.size()-1,j=b.s.size()-1,br=0;
        while(i>=0){
            int a=s[i--]-'0';
            int d=0;
            if(j>=0) d=b.s[j--]-'0';
            int v=a-d-br;
            if(v<0){v+=10;br=1;}
            else br=0;
            r.push_back(char(v+'0'));
        }
        while(r.size()>1 && r.back()=='0') r.pop_back();
        reverse(r.begin(),r.end());
        return BigInt(r);
    }

    BigInt operator*(BigInt b){
        int n=s.size(),m=b.s.size();
        vector<int> a(n+m);
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                int v=(s[i]-'0')*(b.s[j]-'0');
                a[i+j+1]+=v;
                a[i+j]+=a[i+j+1]/10;
                a[i+j+1]%=10;
            }
        }
        string r="";
        for(int i=0;i<a.size();i++){
            if(!(r.empty()&&a[i]==0)) r.push_back(a[i]+'0');
        }
        if(r=="") r="0";
        return BigInt(r);
    }

    BigInt operator/(BigInt b){
        if(b.s=="0") return BigInt("Error");
        string ans="",cur="";
        for(int i=0;i<s.size();i++){
            cur.push_back(s[i]);
            while(cur.size()>1&&cur[0]=='0') cur.erase(cur.begin());
            BigInt t(cur);
            int cnt=0;
            while(!t.lessThan(b)){
                t=t-b;
                cnt++;
            }
            cur=t.s;
            ans.push_back(cnt+'0');
        }
        int p=0;
        while(p+1<ans.size() && ans[p]=='0') p++;
        return BigInt(ans.substr(p));
    }
};

int main(){
    BigInt a("53855989754"),b("4384928");
    cout<<(a+b).s<<"\n";
    cout<<(a-b).s<<"\n";
    cout<<(a*b).s<<"\n";
    cout<<(a/b).s<<"\n";

    return 0;
}
