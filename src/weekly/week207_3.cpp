
#include <vector>

using namespace std;

class Solution {
public:
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<ll>> max_prod(n, vector<ll>(m)), min_prod(n, vector<ll>(m));
        max_prod[0][0] = (ll)grid[0][0];
        min_prod[0][0] = (ll)grid[0][0];
        for(int i = 1; i < n; ++i)
        {
            if(grid[i][0] > 0)
            {
                max_prod[i][0] = max_prod[i - 1][0] * grid[i][0];
                min_prod[i][0] = min_prod[i - 1][0] * grid[i][0];
            }
            else if(grid[i][0] < 0)
            {
                max_prod[i][0] = min_prod[i - 1][0] * grid[i][0];
                min_prod[i][0] = max_prod[i - 1][0] * grid[i][0];
            }
        }
        for(int j = 1; j < m; ++j)
        {
            if(grid[0][j] > 0)
            {
                max_prod[0][j] = max_prod[0][j - 1] * grid[0][j];
                min_prod[0][j] = min_prod[0][j - 1] * grid[0][j];
            }
            else if(grid[0][j] < 0)
            {
                max_prod[0][j] = min_prod[0][j - 1] * grid[0][j];
                min_prod[0][j] = max_prod[0][j - 1] * grid[0][j];
            }
        }
        for(int i = 1; i < n; ++i)
            for(int j = 1; j < m; ++j)
            {
                if(grid[i][j] > 0)
                {
                    max_prod[i][j] = max(max_prod[i - 1][j] * grid[i][j], max_prod[i][j - 1] * grid[i][j]);
                    min_prod[i][j] = min(min_prod[i - 1][j] * grid[i][j], min_prod[i][j - 1] * grid[i][j]);
                }
                else if(grid[i][j] < 0)
                {
                    max_prod[i][j] = max(min_prod[i - 1][j] * grid[i][j], min_prod[i][j - 1] * grid[i][j]);
                    min_prod[i][j] = min(max_prod[i - 1][j] * grid[i][j], max_prod[i][j - 1] * grid[i][j]);
                }
            }
        if(max_prod[n - 1][m - 1] < 0)
            return -1;
        return max_prod[n - 1][m - 1] % MOD;
    }

private:
    const int MOD = 1e9 + 7;
    using ll = long long;
};
