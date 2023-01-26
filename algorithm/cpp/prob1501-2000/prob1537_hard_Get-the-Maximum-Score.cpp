// prob1537: Get the Maximum Score

/*
 * https://leetcode-cn.com/problems/get-the-maximum-score/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        nums[0] = nums1;
        nums[1] = nums2;
        for(int k = 0; k <= 1; ++k)
        {
            int n = nums[k].size();
            dp[k][0].assign(n, -1);
            dp[k][1].assign(n, -1);
            for(int i = 0; i < (int)nums[k].size(); ++i)
                mapping[k][nums[k][i]] = i;
        }
        int n1 = nums1.size(), n2 = nums2.size();
        ll ans1 = solve(0, 0, n1 - 1);
        ll ans2 = solve(1, 0, n2 - 1);
        return max(ans1, ans2) % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    vector<ll> dp[2][2];
    unordered_map<int, int> mapping[2];
    vector<int> nums[2];

    ll solve(int k, int jump, int i)
    {
        if(i < 0) return 0;
        if(dp[k][jump][i] != -1)
            return dp[k][jump][i];
        if(jump == 1)
            return dp[k][jump][i] = solve(k, 0, i - 1);
        dp[k][jump][i] = nums[k][i] + solve(k, 0, i - 1);
        if(mapping[k ^ 1].count(nums[k][i]) != 0)
            dp[k][jump][i] = max(dp[k][jump][i], nums[k][i] + solve(k ^ 1, 1, mapping[k ^ 1][nums[k][i]]));
        return dp[k][jump][i];
    }
};


class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        vector<ll> f(n1 + 1);
        vector<ll> g(n2 + 1);
        int i = 1, j = 1;
        while(i <= n1 && j <= n2)
        {
            if(nums1[i - 1] < nums2[j - 1])
            {
                f[i] = f[i - 1] + nums1[i - 1];
                ++i;
            }
            else if(nums1[i - 1] > nums2[j - 1])
            {
                g[j] = g[j - 1] + nums2[j - 1];
                ++j;
            }
            else
            {
                f[i] = nums1[i - 1] + max(f[i - 1], g[j - 1]);
                g[j] = f[i];
                ++i;
                ++j;
            }
        }
        while(i <= n1)
        {
            f[i] = f[i - 1] + nums1[i - 1];
            ++i;
        }
        while(j <= n2)
        {
            g[j] = g[j - 1] + nums2[j - 1];
            ++j;
        }
        return max(f[n1], g[n2]) % MOD;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
};
