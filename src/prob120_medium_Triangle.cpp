// prob120: Triangle

/*
 * Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
 */

/*
 * For example, given the following triangle
 * [
 *      [2],
 *     [3,4],
 *    [6,5,7],
 *   [4,1,8,3]
 * ]
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.empty()) return 0;
        int n = triangle.size();
        if(n == 1) return triangle[0][0];
        vector<int> dp(n + 1, INT_MAX);
        dp[1] = triangle[0][0];
        for(int i = 1; i < n; ++i)
            for(int j = i + 1; j >= 1; --j)
                dp[j] = min(dp[j], dp[j - 1]) + triangle[i][j - 1];
        int result = dp[1];
        for(int i = 2; i <= n; ++i)
            result = min(result, dp[i]);
        return result;
    }
};
