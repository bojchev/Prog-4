#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

vector<int> findPattern(string& pattern, string& text)
{
    int base = 13;
    int mod = 1e9 + 9;
    vector<long long> power(max(pattern.size(), text.size()));
    power[0] = 1;
    for (int i = 1; i < max(pattern.size(), text.size()); i++)
    {
        power[i] = (power[i - 1] * base) % mod;
    }

    vector<long long> prefixHash(text.size() + 1, 0);
    for (int i = 0; i < text.size(); i++)
    {
        prefixHash[i + 1] = (prefixHash[i] + (text[i] - 'a' + 1) * power[i]) % mod;
    }

    long long patternHash = 0;
    for (int i = 0; i < pattern.size(); i++)
    {
        patternHash = (patternHash + (pattern[i] - 'a' + 1) * power[i]) % mod;
    }

    vector<int> matches;
    for (int i = 0; i + pattern.size() - 1 < text.size(); i++)
    {
        long long substringHash = (prefixHash[i + pattern.size()] + mod - prefixHash[i]) % mod;
        if (substringHash == patternHash * power[i] % mod)
        {
            matches.push_back(i);
        }
    }
    return matches;
}

int main()
{
    string pattern, text;
    cin >> pattern >> text;
    vector<int> result = findPattern(pattern, text);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << '\n';
    return 0;
}
