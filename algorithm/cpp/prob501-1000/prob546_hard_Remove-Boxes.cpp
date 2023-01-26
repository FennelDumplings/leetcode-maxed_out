// prob546: Remove Boxes

/*
 * Given several boxes with different colors represented by different positive numbers.
 * You may experience several rounds to remove boxes until there is no box left. Each time you can choose some continuous boxes with the same color (composed of k boxes, k >= 1), remove them and get k*k points.
 * Find the maximum points you can get.
 */

/*
 * Example 1:
 *
 * Input: boxes = [1,3,2,2,2,3,4,3,1]
 * Output: 23
 * Explanation:
 * [1, 3, 2, 2, 2, 3, 4, 3, 1]
 * ----> [1, 3, 3, 4, 3, 1] (3*3=9 points)
 *  ----> [1, 3, 3, 3, 1] (1*1=1 points)
 *  ----> [1, 1] (3*3=9 points)
 *  ----> [] (2*2=4 points)
 */

/*
 * Constraints:
 * 1 <= boxes.length <= 100
 * 1 <= boxes[i] <= 100
 */

#include <vector>
#include <cstring>

using namespace std;

// dp[i][j][k] := [i..j] 上, [j+1..n-1] 有 k 个与 b[j] 相同的
// dp[i][j][k] = 0 // j < i
// dp[0][n - 1][0] 为答案
// dp[i][j][k] =
//      dp[i][j - 1][0] + (k + 1)^2  if 删 b[j] 共 k + 1 个
//      dp[i][p][k + 1] + dp[p + 1][j - 1][0]     if 删分割点 p, i <= p < j, 且 b[p] == b[j]
//  850ms
class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        if(boxes.empty()) return 0;
        int n = boxes.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n)));
        return solve(0, n - 1, 0, boxes, dp);
    }

private:
    int solve(int l, int r, int k, const vector<int>& boxes, vector<vector<vector<int>>>& dp)
    {
        if(l > r)
            return 0;
        if(dp[l][r][k] > 0 )
            return dp[l][r][k];
        dp[l][r][k] = solve(l, r - 1, 0, boxes, dp) + (k + 1)*(k + 1);
        for(int i = l; i < r; ++i)
        {
            if(boxes[i] == boxes[r])
                dp[l][r][k] = max(dp[l][r][k], solve(l, i, k + 1, boxes, dp) + solve(i + 1, r - 1, 0, boxes, dp));
        }
        return dp[l][r][k];
    }
};

// 用全局数组
// 850 -> 320 ms
int dp[105][105][105];
class Solution_2 {
public:
    int removeBoxes(vector<int>& boxes) {
        if(boxes.empty()) return 0;
        int n = boxes.size();
        memset(dp, 0, sizeof(dp));
        return solve(0, n - 1, 0, boxes);
    }

private:
    int solve(int l, int r, int k, const vector<int>& boxes)
    {
        if(l > r)
            return 0;
        if(dp[l][r][k] > 0 )
            return dp[l][r][k];
        dp[l][r][k] = solve(l, r - 1, 0, boxes) + (k + 1)*(k + 1);
        for(int i = l; i < r; ++i)
        {
            if(boxes[i] == boxes[r])
                dp[l][r][k] = max(dp[l][r][k], solve(l, i, k + 1, boxes) + solve(i + 1, r - 1, 0, boxes));
        }
        return dp[l][r][k];
    }
};


// 用全局数组
// 850 -> 320 ms
// 加剪枝
// int dp[105][105][105];
// 302 -> 64 ms
class Solution_3 {
public:
    int removeBoxes(vector<int>& boxes) {
        if(boxes.empty()) return 0;
        int n = boxes.size();
        memset(dp, 0, sizeof(dp));
        return solve(0, n - 1, 0, boxes);
    }

private:
    int solve(int l, int r, int k, const vector<int>& boxes)
    {
        if(l > r)
            return 0;
        if(dp[l][r][k] > 0 )
            return dp[l][r][k];
        while(r - 1 >= l && boxes[r - 1] == boxes[r])
        {
            --r;
            ++k;
        }
        dp[l][r][k] = solve(l, r - 1, 0, boxes) + (k + 1)*(k + 1);
        for(int i = l; i < r; ++i)
        {
            if(boxes[i] == boxes[r])
                dp[l][r][k] = max(dp[l][r][k], solve(l, i, k + 1, boxes) + solve(i + 1, r - 1, 0, boxes));
        }
        return dp[l][r][k];
    }
};

