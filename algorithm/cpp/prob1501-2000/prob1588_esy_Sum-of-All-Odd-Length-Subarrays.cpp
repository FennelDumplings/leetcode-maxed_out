// prob1588: Sum of All Odd Length Subarrays

/*
 * https://leetcode-cn.com/problems/sum-of-all-odd-length-subarrays/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size();
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1]+ arr[i - 1];
        int max_len = n;
        if((max_len & 1) == 0)
            --max_len;
        int ans = 0;
        for(int len = max_len; len >= 1; len -= 2)
        {
            for(int i = 0; i <= n - len; ++i)
            {
                int j = i + len - 1;
                ans += sums[j + 1] - sums[i];
            }
        }
        return ans;
    }
};
