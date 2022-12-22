class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size();
        dp = vector<int>(1 << n, -1);
        return solve(0, nums, 1);
    }

private:
    vector<int> dp;
    int solve(int state, const vector<int>& nums, int r)
    {
        if(dp[state] != -1)
            return dp[state];
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            if(state >> i & 1)
                continue;
            for(int j = i + 1; j < n; ++j)
            {
                if(state >> j & 1)
                    continue;
                ans = max(ans, r * (gcd<int>(nums[i], nums[j])) + solve(state | (1 << i) | (1 << j), nums, r + 1));
            }
        }
        dp[state] = ans;
        return ans;
    }
};
