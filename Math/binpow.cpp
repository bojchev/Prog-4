#include <bits/stdc++.h>
using namespace std;

struct BigInt{
    string v;

    BigInt(string x="0"){ v=x; }

    bool operator<(BigInt b) const{
        if(v.size()!=b.v.size()) return v.size()<b.v.size();
        return v<b.v;
    }

    bool operator==(BigInt b) const{
        return v==b.v;
    }

    BigInt operator+(BigInt b) const{
        string r="";
        int i=v.size()-1,j=b.v.size()-1,cr=0;
        while(i>=0||j>=0||cr){
            int t=cr;
            if(i>=0) t+=v[i--]-'0';
            if(j>=0) t+=b.v[j--]-'0';
            r.push_back(char(t%10+'0'));
            cr=t/10;
        }
        reverse(r.begin(),r.end());
        return BigInt(r);
    }

    BigInt operator-(BigInt b) const{
        string r="";
        int i=v.size()-1,j=b.v.size()-1,br=0;
        while(i>=0){
            int t=(v[i--]-'0')-br-(j>=0?b.v[j--]-'0':0);
            if(t<0){t+=10;br=1;} else br=0;
            r.push_back(char(t+'0'));
        }
        while(r.size()>1 && r.back()=='0') r.pop_back();
        reverse(r.begin(),r.end());
        return BigInt(r);
    }

    BigInt operator*(BigInt b) const{
        int n=v.size(),m=b.v.size();
        vector<int>a(n+m);
        for(int i=n-1;i>=0;i--)
            for(int j=m-1;j>=0;j--)
                a[i+j+1]+=(v[i]-'0')*(b.v[j]-'0');
        for(int i=n+m-1;i>0;i--){
            a[i-1]+=a[i]/10;
            a[i]%=10;
        }
        string r="";
        for(int x:a) if(!(r.empty()&&x==0)) r.push_back(x+'0');
        if(r=="") r="0";
        return BigInt(r);
    }

    pair<BigInt,BigInt> divmod(BigInt b) const{
        if(b==BigInt("0")) return {BigInt("Error"),BigInt("Error")};
        string q="",cur="";
        for(char c:v){
            cur.push_back(c);
            while(cur.size()>1&&cur[0]=='0') cur.erase(cur.begin());
            BigInt rem(cur);
            int cnt=0;
            while(!(rem<b)){
                rem=rem-b;
                cur=rem.v;
                cnt++;
            }
            q.push_back(cnt+'0');
        }
        int p=0;
        while(p+1<q.size()&&q[p]=='0') p++;
        q=q.substr(p);
        if(q=="") q="0";
        return {BigInt(q),BigInt(cur==""?"0":cur)};
    }

    BigInt operator/(BigInt b) const{ return divmod(b).first; }
    BigInt operator%(BigInt b) const{ return divmod(b).second; }
};

BigInt modPow(BigInt b,BigInt e,BigInt m){
    BigInt r("1");
    b=b%m;
    while(!(e==BigInt("0"))){
        if(!(e%BigInt("2")==BigInt("0")))
            r=(r*b)%m;
        b=(b*b)%m;
        e=e/BigInt("2");
    }
    return r;
}

int main(){
    BigInt a("8"),e("17"),m("90");
    BigInt ans=modPow(a,e,m);
    cout<<ans.v<<"\n";
    return 0;
}
