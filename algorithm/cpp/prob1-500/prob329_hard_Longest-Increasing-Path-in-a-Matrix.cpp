// prob329: Longest Increasing Path in a Matrix

/*
 * Given an integer matrix, find the length of the longest increasing path.
 * From each cell, you can either move to four directions: left, right, up or down.
 * You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
 */

/*
 * Example 1:
 * Input: nums =
 * [
 *   [9,9,4],
 *   [6,6,8],
 *   [2,1,1]
 * ]
 * Output: 4
 * Explanation: The longest increasing path is [1, 2, 6, 9].
 * Example 2:
 *
 * Input: nums =
 * [
 *   [3,4,5],
 *   [3,2,6],
 *   [2,2,1]
 * ]
 * Output: 4
 * Explanation: The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
 */

#include <vector>
#include <queue>

using namespace std;

// 记忆化
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        int result = 0;
        vector<vector<int> > dp(n, vector<int>(m, -1));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                result = max(result, _dp(i, j, dp, matrix));
        return result;
    }

private:
    int _dp(int i, int j, vector<vector<int> >& dp, vector<vector<int> >& matrix)
    {
        if(dp[i][j] != -1) return dp[i][j];

        int n = matrix.size(), m = matrix[0].size();
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        dp[i][j] = 0;
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x >= 0 && x < n && y >= 0 && y < m && matrix[i][j] > matrix[x][y])
                dp[i][j] = max(dp[i][j], _dp(x, y, dp, matrix));
        }
        ++dp[i][j];
        return dp[i][j];
    }
};

// 拓扑排序
class Solution_2 {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty()) return 0;
        int n = matrix.size(), m = matrix[0].size();
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        vector<vector<int> > outdegrees(n, vector<int>(m, 0));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if(x >= 0 && x < n && y >= 0 && y < m && matrix[i][j] < matrix[x][y])
                        ++outdegrees[i][j];
                }
        using PII = pair<int, int>;
        queue<PII> q;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                if(outdegrees[i][j] == 0)
                    q.push(PII(i, j));

        int result = 0;
        vector<PII> level_nodes;
        while(!q.empty())
        {
            ++result;
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(PII p: level_nodes)
            {
                int i = p.first;
                int j = p.second;
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if(x >= 0 && x < n && y >= 0 && y < m && matrix[i][j] > matrix[x][y])
                        if(--outdegrees[x][y] == 0)
                            q.push(PII(x, y));
                }
            }
        }
        return result;
    }
};
