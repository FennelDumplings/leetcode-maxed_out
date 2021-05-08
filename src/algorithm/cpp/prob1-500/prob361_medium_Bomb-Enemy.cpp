// prob361: Bomb Enemy

/*
 * Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
 * The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
 * Note: You can only put the bomb at an empty cell.
 */

/*
 * Example:
 * Input: [["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]]
 * Output: 3
 * Explanation: For the given grid,
 * 0 E 0 0
 * E 0 W E
 * 0 E 0 0
 * Placing a bomb at (1,1) kills 3 enemies.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        int result = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] != '0') continue;
                if(visited[i][j]) continue;
                int ne = 0;
                visited[i][j] = true;
                int iter_up = i - 1;
                while(iter_up >= 0 && grid[iter_up][j] != 'W')
                {
                    // visited[iter_up][j] = true;
                    if(grid[iter_up][j] == 'E')
                        ++ne;
                    --iter_up;
                }
                int iter_down = i + 1;
                while(iter_down < n && grid[iter_down][j] != 'W')
                {
                    // visited[iter_down][j] = true;
                    if(grid[iter_down][j] == 'E')
                        ++ne;
                    ++iter_down;
                }
                int iter_left = j - 1;
                while(iter_left >= 0 && grid[i][iter_left] != 'W')
                {
                    // visited[i][iter_left] = true;
                    if(grid[i][iter_left] == 'E')
                        ++ne;
                    --iter_left;
                }
                int iter_right = j + 1;
                while(iter_right < m && grid[i][iter_right] != 'W')
                {
                    // visited[i][iter_right] = true;
                    if(grid[i][iter_right] == 'E')
                        ++ne;
                    ++iter_right;
                }
                result = max(result, ne);
            }
        return result;
    }
};
