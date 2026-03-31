#include <iostream>
#include <cstdint>

using namespace std;
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpow(u64 b, u64 e, u64 mod) {
    u64 r = 1;
    b %= mod;
    while (e) {
        if (e & 1)
            r = (u128)r * b % mod;
        b = (u128)b * b % mod;
        e >>= 1;
    }
    return r;
}

bool slozhen(u64 n, u64 a, u64 d, int s) {
    u64 x = binpow(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=5) {
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (slozhen(n, a, d, s))
            return false;
    }
    return true;
}

int main()
{
    u64 n;
    cin >> n;
    if(MillerRabin(n, 5)){
        cout<<"valjda";
    }
    else{
        cout<<"ne";
    }
}
