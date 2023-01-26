// prob750: Number Of Corner Rectangles

/*
 * https://leetcode-cn.com/problems/number-of-corner-rectangles/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        if(n == 1 || m == 1) return 0;
        vector<vector<int>> dp(m, vector<int>(m, -1));
        for(int j = 0; j < m - 1; ++j)
            for(int k = j + 1; k < m; ++k)
                if(grid[0][j] == 1 && grid[0][k] == 1)
                    dp[j][k] = 0;
        int ans = 0;
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m - 1; ++j)
                for(int k = j + 1; k < m; ++k)
                {
                    if(grid[i][j] == 1 && grid[i][k] == 1)
                    {
                        ++dp[j][k];
                        ans += dp[j][k];
                    }
                }
        return ans;
    }
};


// 加一行优化
class Solution_2 {
public:
    int countCornerRectangles(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        if(n == 1 || m == 1) return 0;
        vector<vector<int>> dp(m, vector<int>(m, -1));
        for(int j = 0; j < m - 1; ++j)
            for(int k = j + 1; k < m; ++k)
                if(grid[0][j] == 1 && grid[0][k] == 1)
                    dp[j][k] = 0;
        int ans = 0;
        for(int i = 1; i < n; ++i)
            for(int j = 0; j < m - 1; ++j)
            {
                if(grid[i][j] == 1)
                    for(int k = j + 1; k < m; ++k)
                    {
                        if(grid[i][k] == 1)
                        {
                            ++dp[j][k];
                            ans += dp[j][k];
                        }
                    }
            }
        return ans;
    }
};
