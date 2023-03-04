vector<int> get_primes(int n) {
    if(n < 2) return {};
    vector<bool> vec(n, true);
    vec[0] = false;
    vec[1] = false;
    int cnt = 0;
    vector<int> primes;
    for(int i = 2; i < n; ++i)
    {
        if(vec[i])
        {
            ++cnt;
            primes.push_back(i);
        }
        for(int j = 0; j < cnt && i * primes[j] < n; ++j)
        {
            vec[i * primes[j]] = false;
            if(i % primes[j] == 0)
                break;
        }
    }
    return primes;
}

class Solution {
public:
    int splitArray(vector<int>& nums) {
        int n = nums.size();
        int maxx = *max_element(nums.begin(), nums.end());
        vector<int> primes = get_primes(maxx + 1);
        vector<int> min_factor(maxx + 1, 0);
        for(int p: primes)
        {
            min_factor[p] = p;
            for(int j = 2 * p; j <= maxx; j += p)
                if(min_factor[j] == 0)
                    min_factor[j] = p;
        }

        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        vector<int> mapping(maxx + 1, n + 1);
        for(int i = 1; i <= n; ++i)
        {
            for(int x = nums[i - 1]; x > 1; x /= min_factor[x])
            {
                int p = min_factor[x];
                mapping[p] = min(mapping[p], dp[i - 1]);
                dp[i] = min(dp[i], 1 + mapping[p]);
            }
        }
        return dp[n];
    }
};
