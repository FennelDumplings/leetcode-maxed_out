// prob1316:Distinct Echo Substrings

/*
 * https://leetcode-cn.com/problems/distinct-echo-substrings/
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        hash = vector<ull>(n + 1);
        pp = vector<ull>(n + 1);
        pp[0] = 1;
        for(int i = 1; i <= n; ++i)
        {
            hash[i] = hash[i - 1] * p;
            hash[i] = hash[i] + text[i - 1];
            pp[i] = pp[i - 1] * p;
        }

        unordered_set<ull> setting;
        for(int len = 1; len * 2 <= n; ++len)
        {
            for(int i = 0; i <= n - len * 2; ++i)
            {
                ull left_hash = query(i, i + len - 1);
                ull right_hash = query(i + len, i + 2 * len - 1);
                if(left_hash != right_hash)
                    continue;
                // if(check(text, len, i, i + len))
                    // setting.insert(text.substr(i, len * 2));
                setting.insert(left_hash);
            }
        }
        return setting.size();
    }

private:
    using ull = unsigned long long;
    const ull p = 201326611;

    vector<ull> hash;
    vector<ull> pp;

    bool check(const string& s, int len, int i, int j)
    {
        for(int k = 0; k < len; ++k)
            if(s[i + k] != s[j + k])
                return false;
        return true;
    }

    ull query(int l, int r)
    {
        int len = r - l + 1;
        return hash[r + 1] - hash[l] * pp[len];
    }
};
