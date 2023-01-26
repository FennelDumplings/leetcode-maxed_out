// prob1402: Reducing Dishes

/*
 * https://leetcode-cn.com/problems/reducing-dishes/
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// s 降序
// dp[i] = dp[i - 1] + sums[i + 1]

class Solution {
public:
    int maxSatisfaction(vector<int>& s) {
        if(s.empty()) return 0;
        sort(s.begin(), s.end(), greater<int>());
        int n = s.size();
        int ans = 0;
        int dp = 0;
        int sum = 0;
        for(int i = 0; i < n; ++i)
        {
            sum += s[i];
            dp = dp + sum;
            ans = max(ans, dp);
        }
        return ans;
    }
};
