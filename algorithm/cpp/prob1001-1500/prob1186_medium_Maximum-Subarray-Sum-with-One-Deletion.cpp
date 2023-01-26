// prob1187: Maximum Subarray Sum with One Deletion

/*
 * https://leetcode-cn.com/problems/maximum-subarray-sum-with-one-deletion/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp1(n), dp2(n);
        dp1[0] = arr[0];
        int ans = arr[0];
        for(int i = 1; i < n; ++i)
        {
            dp1[i] = max(dp1[i - 1] + arr[i], arr[i]);
            ans = max(ans, dp1[i]);
        }
        dp2[n - 1] = arr[n - 1];
        for(int i = n - 2; i >= 0; --i)
            dp2[i] = max(dp2[i + 1] + arr[i], arr[i]);
        for(int p = 1; p < n - 1; ++p)
            ans = max(ans, dp1[p - 1] + dp2[p + 1]);
        return ans;
    }
};
