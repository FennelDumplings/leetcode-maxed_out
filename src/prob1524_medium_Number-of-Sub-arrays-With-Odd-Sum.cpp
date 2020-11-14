// prob1524: Number of Sub-arrays With Odd Sum

/*
 * https://leetcode-cn.com/problems/number-of-sub-arrays-with-odd-sum/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int n = arr.size();
        using ll = long long;
        const int MOD = 1e9 + 7;
        ll prev = arr[0] & 1;
        ll ans = prev;
        for(int i = 1; i < n; ++i)
        {
            if(arr[i] & 1)
            {
                ans = (ans + i - prev + 1) % MOD;
                prev = (i - prev + 1) % MOD;
            }
            else
            {
                ans = (ans + prev) % MOD;
            }
        }
        return ans;
    }
};
