// prob1260: Shift 2D Grid

/*
 * https://leetcode-cn.com/problems/shift-2d-grid/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        if(grid.empty()) return {};
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> result(m, vector<int>(n, 0));
        for(int i = 0; i < m; ++i)
            for(int j = 0; j < n; ++j)
            {
                PII nxt = f(i, j, k, m, n);
                result[nxt.first][nxt.second] = grid[i][j];
            }
        return result;
    }

private:
    using PII = pair<int, int>;

    PII f(int i, int j, int k, int m, int n)
    {
        int N = n * m;
        int offset = i * n + j;
        int new_offset = (offset + k) % N;
        return PII(new_offset / n, new_offset % n);
    }
};
