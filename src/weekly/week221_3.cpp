
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findBall(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> result(m, 0);
        for(int j = 0; j < m; ++j)
        {
            result[j] = dfs(grid, 0, j, n, m);
        }
        return result;
    }

private:
    int dfs(const vector<vector<int>>& grid, int i, int j, int n, int m)
    {
        if(i == n)
        {
            return j;
        }
        if(grid[i][j] == 1)
        {
            if(j == m - 1 || grid[i][j + 1] == -1)
                return -1;
            else
                return dfs(grid, i + 1, j + 1, n, m);
        }
        else
        {
            if(j == 0 || grid[i][j - 1] == 1)
                return -1;
            else
                return dfs(grid, i + 1, j - 1, n, m);
        }
    }
};
