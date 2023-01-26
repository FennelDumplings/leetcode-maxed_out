// prob656: Coin Path

/*
 * https://leetcode-cn.com/problems/coin-path/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> cheapestJump(vector<int>& A, int B) {
        int n = A.size();
        if(A[n - 1] == -1) return {};
        vector<int> dp(n, -1);
        dp[n - 1] = 0;
        for(int i = n - 2; i >= 0; --i)
        {
            if(A[i] == -1) continue;
            for(int j = i + 1; j <= min(n - 1, i + B); ++j)
            {
                if(dp[j] == -1) continue;
                if(dp[i] == -1)
                    dp[i] = dp[j] + A[i];
                else
                    dp[i] = min(dp[i], dp[j] + A[i]);
            }
        }
        if(dp[0] == -1) return {};
        vector<int> result;
        int iter = 0;
        while(iter != n - 1)
        {
            result.push_back(iter + 1);
            for(int j = iter + 1; j <= min(n - 1, iter + B); ++j)
            {
                if(dp[j] != -1 && dp[j] + A[iter] == dp[iter])
                {
                    iter = j;
                    break;
                }
            }
        }
        result.push_back(n);
        return result;
    }
};
