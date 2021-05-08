// prob1449: Form Largest Integer With Digits That Add up to Target

/*
 * https://leetcode-cn.com/problems/form-largest-integer-with-digits-that-add-up-to-target/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        int n = cost.size();
        vector<vector<int>> dp(n, vector<int>(target + 1, -1));
        for(int i = 0; i < n; ++i)
            dp[i][0] = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 1; j <= target; ++j)
            {
                if(i > 0)
                    dp[i][j] = dp[i - 1][j];
                if(j - cost[i] >= 0 && dp[i][j - cost[i]] != -1)
                    dp[i][j] = max(dp[i][j], dp[i][j - cost[i]] + 1);
            }
        }
        if(dp[n - 1][target] == -1)
            return "0";
        string result;
        int i = 8;
        int j = target;
        while(j > 0)
        {
            if(j - cost[i] >= 0 && dp[i][j - cost[i]] + 1 == dp[i][j])
            {
                j -= cost[i];
                result += '0' + i + 1;
            }
            else
                --i;
        }
        return result;
    }
};
