#include <bits/stdc++.h>
using namespace std;

class BigInt {
public:
    string v;

    BigInt(string s = "0") { v = s; }

    bool isLess(BigInt o) {
        if (v.size() != o.v.size()) return v.size() < o.v.size();
        return v < o.v;
    }

    BigInt operator+(BigInt o) {
        string r = "";
        int i = v.size() - 1, j = o.v.size() - 1, c = 0;
        while (i >= 0 || j >= 0 || c) {
            int a = (i >= 0) ? v[i--] - '0' : 0;
            int b = (j >= 0) ? o.v[j--] - '0' : 0;
            int sum = a + b + c;
            r += (char)(sum % 10 + '0');
            c = sum / 10;
        }
        reverse(r.begin(), r.end());
        return BigInt(r);
    }

    BigInt operator*(BigInt o) {
        int n = v.size(), m = o.v.size();
        vector<int> r(n + m, 0);

        for (int i = n - 1; i >= 0; i--) {
            for (int j = m - 1; j >= 0; j--) {
                int mul = (v[i] - '0') * (o.v[j] - '0');
                int sum = mul + r[i + j + 1];
                r[i + j + 1] = sum % 10;
                r[i + j] += sum / 10;
            }
        }

        string s = "";
        for (int x : r) if (!(s.empty() && x == 0)) s += (char)(x + '0');
        return s == "" ? BigInt("0") : BigInt(s);
    }
};

struct Compare {
    bool operator()(pair<BigInt, BigInt> a, pair<BigInt, BigInt> b) {
        return b.first.isLess(a.first);
    }
};

void genP(int n) {
    priority_queue<pair<BigInt, BigInt>, vector<pair<BigInt, BigInt>>, Compare> pq;

    cout << "2 ";
    pq.push({BigInt("4"), BigInt("2")});

    for (int i = 3; i <= n; i++) {
        BigInt c(to_string(i));

        if (c.isLess(pq.top().first)) {
            cout << i << " ";
            pq.push({c * c, c});
        } else {
            while (!c.isLess(pq.top().first)) {
                pair<BigInt, BigInt> t = pq.top();
                pq.pop();
                BigInt nm = t.first;
                BigInt p = t.second;
                pq.push({nm + p, p});
            }
        }
    }
    cout << endl;
}

int main() {
    int z;
    cin >> z;
    genP(z);
    return 0;
}
