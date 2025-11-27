class Solution {
public:
    string longestDupSubstring(string s) {
        int left = 1, right = s.size() - 1;
        int start = 0, maxLen = 0;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int pos = search(s, mid);
            if (pos != -1)
            {
                start = pos;
                maxLen = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return s.substr(start, maxLen);
    }

private:
    int search(string& s, int len)
    {
        int base = 31;
        long long mod = 1e9 + 7;
        int n = s.size();

        long long powerLen = 1;
        for (int i = 0; i < len; i++)
        {
            powerLen = (powerLen * base) % mod;
        }

        vector<pair<long long, int>> hashes;

        long long hash = 0;
        for (int i = 0; i < len; i++)
        {
            hash = (hash * base + (s[i] - 'a' + 1)) % mod;
        }
        hashes.push_back({hash, 0});

        for (int i = len; i < n; i++)
        {
            hash = (hash * base - (s[i - len] - 'a' + 1) * powerLen % mod + mod) % mod;
            hash = (hash + (s[i] - 'a' + 1)) % mod;
            hashes.push_back({hash, i - len + 1});
        }

        sort(hashes.begin(), hashes.end());

        for (int i = 1; i < hashes.size(); i++)
        {
            if (hashes[i].first == hashes[i - 1].first)
            {
                string s1 = s.substr(hashes[i].second, len);
                string s2 = s.substr(hashes[i - 1].second, len);
                if (s1 == s2)
                {
                    return hashes[i].second;
                }
            }
        }
        return -1;
    }
};

