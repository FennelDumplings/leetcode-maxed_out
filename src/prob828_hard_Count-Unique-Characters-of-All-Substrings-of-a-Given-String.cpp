// prob8282: Count Unique Characters of All Substrings of a Given String

/*
 * https://leetcode-cn.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        vector<int> L(n, -1), R(n, n);
        vector<int> mapping(26, -1);
        for(int i = 0; i < n; ++i)
        {
            L[i] = mapping[s[i] - 'A'];
            mapping[s[i] - 'A'] = i;
        }
        mapping.assign(26, n);
        for(int i = n - 1; i >= 0; --i)
        {
            R[i] = mapping[s[i] - 'A'];
            mapping[s[i] - 'A'] = i;
        }
        const int MOD = 1e9 + 7;
        using ll = long long;
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            ans = (ans + (ll)(i - L[i]) * (ll)(R[i] - i)) % MOD;
        }
        return ans;
    }
};
