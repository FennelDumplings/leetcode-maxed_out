// prob1191: K-Concatenation Maximum Sum

/*
 * https://leetcode-cn.com/problems/k-concatenation-maximum-sum/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        // dp1[i] := [0..i] 上以 i 为结尾的最大字段和
        // dp2[i] := [i..n-1] 上以 i 为开头的最大字段和
        // sum := arr[0..n-1] 的和
        int n = arr.size();
        vector<int> dp1(n, 0);
        vector<int> dp2(n, 0);
        dp1[0] = arr[0];
        dp2[n - 1] = arr[n - 1];
        ll sum = arr[0];
        ll ans = max(0, arr[0]);
        for(int i = 1; i < n; ++i)
        {
            sum += arr[i];
            dp1[i] = arr[i] + max(dp1[i - 1], 0);
            ans = max(ans, (ll)dp1[i]);
        }
        // 此时 ans 为单串最大子段和
        for(int i = n - 2; i >= 0; --i)
            dp2[i] = arr[i] + max(dp2[i + 1], 0);
        // dp1[n - 1] > 0 且 dp2[0] > 0 可以跨串
        if(dp1[n - 1] > 0 && dp2[0] > 0 && k > 1)
            ans = max(ans, (ll)dp1[n - 1] + dp2[0]);
        // sum > 0 则跨多串
        if(sum > 0 && k > 1)
            ans = max(ans, (dp1[n - 1] + (ll)dp2[0] + (k - 2) * sum));
        return ans % MOD;
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;
};
