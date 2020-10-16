// prob1573: Number of Ways to Split a String

/*
 * https://leetcode-cn.com/problems/number-of-ways-to-split-a-string/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int numWays(string s) {
        const int MOD = 1e9 + 7;
        int n = s.size();
        vector<int> idxs;
        for(int i = 0; i < n; ++i)
        {
            if(s[i] == '1')
                idxs.push_back(i);
        }
        int m = idxs.size();
        if(m % 3 != 0)
            return 0;
        if(m == 0)
        {
            return ((n - 1) * (long long)(n- 2) / 2) % MOD;
        }
        int m1 = idxs[m / 3] - idxs[m / 3 - 1];
        int m2 = idxs[m / 3 * 2] - idxs[m / 3 * 2 - 1];
        return (m1 * (long long)m2) % MOD;
    }
};
