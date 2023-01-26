// prob467: Unique Substrings in Wraparound String

/*
 * https://leetcode-cn.com/problems/unique-substrings-in-wraparound-string/
 */

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int findSubstringInWraproundString(string p) {
        int n = p.size();
        vector<int> dp(26, 0);
        int left = 0;
        while(left < n)
        {
            char cur = p[left];
            int right = left + 1;
            while(right < n && (p[right - 1] - 'a' + 1) % 26 == p[right] - 'a')
                ++right;
            int len = right - left;
            for(int k = 0; k < len; ++k)
            {
                dp[(cur - 'a' + k) % 26] = max(dp[(cur - 'a' + k) % 26], len - k);
            }
            left = right;
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }
};
