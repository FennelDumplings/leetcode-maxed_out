using ll = long long;
const int MOD = 1e9 + 7;

int quickpower_mod(int a, int n, int mod) // 处理不了n是负数
{
    int ans = 1;
    while(n)
    {
        if(n & 1)
            ans = ((ll)ans * a) % mod;
        a = (ll)a * a % mod;
        n >>= 1;
    }
    return ans % mod;
}

class Solution {
public:
    int countPartitions(vector<int>& nums, int K) {
        int sum = 0;
        bool flag = false;
        for(int x: nums)
        {
            sum += x;
            if(sum >= K * 2)
            {
                flag = true;
                break;
            }
        }
        if(!flag)
            return 0;
        int n = nums.size();
        vector<vector<int>> dp(n + 1, vector<int>(K, 0));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i)
            for(int k = 0; k < K; ++k)
            {
                dp[i][k] = dp[i - 1][k];
                if(k >= nums[i - 1])
                    dp[i][k] = ((ll)dp[i][k] + dp[i - 1][k - nums[i - 1]]) % MOD;
            }
        int x = 0;
        for(int k = 0; k < K; ++k)
            x = ((ll)x + dp[n][k]) % MOD;
        int ans = quickpower_mod(2, n, MOD);
        ans = ((ans - (ll)x * 2 % MOD) + MOD) % MOD;
        return ans;
    }
};
