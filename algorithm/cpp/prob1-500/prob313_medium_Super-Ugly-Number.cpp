// prob313: Super Ugly Number

/*
 * https://leetcode-cn.com/problems/super-ugly-number/
 */

#include <set>
#include <vector>

using namespace std;

class Solution_2 {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        using ll = long long;
        set<ll> setting;
        setting.insert(1);
        ll ans = 1;
        for(int i = 1; i <= n; ++i)
        {
            auto it = setting.begin();
            ans = *it;
            setting.erase(it);
            for(int p: primes)
                setting.insert(ans * p);
        }
        return ans;
    }
};

#include <climits>

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        using ll = long long;
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = 1;
        int m = primes.size();
        vector<int> idx(m, 1);
        for(int i = 2; i <= n; ++i)
        {
            int j_min = m;
            for(int j = 0; j < m; ++j)
            {
                if(dp[i] > dp[idx[j]] * primes[j])
                {
                    dp[i] = dp[idx[j]] * primes[j];
                    j_min = j;
                }
            }
            for(int j = 0; j < m; ++j)
                if(dp[idx[j]] * primes[j] == dp[j])
                    ++idx[j];
        }
        return dp[n];
    }
};


