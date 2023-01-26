// prob1289: Minimum Falling Path Sum II

/*
 * Given a square grid of integers arr, a falling path with non-zero shifts is a choice of exactly one element from each row of arr, such that no two elements chosen in adjacent rows are in the same column.
 * Return the minimum sum of a falling path with non-zero shifts.
 */

/*
 * Example 1:
 * Input: arr = [[1,2,3],[4,5,6],[7,8,9]]
 * Output: 13
 * Explanation:
 * The possible falling paths are:
 * [1,5,9], [1,5,7], [1,6,7], [1,6,8],
 * [2,4,8], [2,4,9], [2,6,7], [2,6,8],
 * [3,4,8], [3,4,9], [3,5,7], [3,5,9]
 * The falling path with the smallest sum is [1,5,7], so the answer is 13.
 */

/*
 * Constraints:
 * 1 <= arr.length == arr[i].length <= 200
 * -99 <= arr[i][j] <= 99
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        int n = arr.size();
        if(n == 1) return arr[0][0];
        vector<vector<int> > dp(n, vector<int>(n, INT_MAX));
        int minx = INT_MAX, sub_minx = INT_MAX;
        for(int j = 0; j < n; ++j)
        {
            dp[0][j] = arr[0][j];
            if(dp[0][j] < minx)
            {
                sub_minx = minx;
                minx = dp[0][j];
            }
            else if(dp[0][j] < sub_minx)
            {
                sub_minx = dp[0][j];
            }
        }
        for(int i = 1; i < n; ++i)
        {
            int cur_minx = INT_MAX, cur_sub_minx = INT_MAX;
            for(int j = 0; j < n; ++j)
            {
                if(dp[i - 1][j] == minx)
                    dp[i][j] = sub_minx + arr[i][j];
                else
                    dp[i][j] = minx + arr[i][j];
                if(dp[i][j] < cur_minx)
                {
                    cur_sub_minx = cur_minx;
                    cur_minx = dp[i][j];
                }
                else if(dp[i][j] < cur_sub_minx)
                {
                    cur_sub_minx = dp[i][j];
                }
            }
            minx = cur_minx;
            sub_minx = cur_sub_minx;
        }
        return minx;
    }
};

// 424ms
// O(N^3)
class Solution_2 {
public:
    int minFallingPathSum(vector<vector<int>>& arr) {
        int n = arr.size();
        vector<vector<int> > dp(n, vector<int>(n, INT_MAX));
        for(int j = 0; j < n; ++j)
            dp[0][j] = arr[0][j];
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                int minx = INT_MAX;
                for(int k = 0; k < n; ++k)
                {
                    if(k == j) continue;
                    minx = min(minx, dp[i - 1][k]);
                }
                dp[i][j] = minx + arr[i][j];
            }
        int result = INT_MAX;
        for(int a: dp[n - 1])
            result = min(result, a);
        return result;
    }
};
