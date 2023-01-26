// prob885: Spiral Matrix III

/*
 * On a 2 dimensional grid with R rows and C columns, we start at (r0, c0) facing east.
 * Here, the north-west corner of the grid is at the first row and column, and the south-east corner of the grid is at the last row and column.
 * Now, we walk in a clockwise spiral shape to visit every position in this grid. 
 * Whenever we would move outside the boundary of the grid, we continue our walk outside the grid (but may return to the grid boundary later.) 
 * Eventually, we reach all R * C spaces of the grid.
 * Return a list of coordinates representing the positions of the grid in the order they were visited.
 */

/*
 * Example 1:
 * Input: R = 1, C = 4, r0 = 0, c0 = 0
 * Output: [[0,0],[0,1],[0,2],[0,3]]
 * Example 2:
 * Input: R = 5, C = 6, r0 = 1, c0 = 4
 * Output: [[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]
 */

/*
 * Note:
 * 1 <= R <= 100
 * 1 <= C <= 100
 * 0 <= r0 < R
 * 0 <= c0 < C
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        vector<vector<int>> result;
        int i = r0, j = c0, d = 0;
        result.push_back({i, j});
        bool up = false, down = false, left = false, right = false;
        int direct_cnt[4] = {0, 0, 0, 0};
        while(true)
        {
            ++direct_cnt[d];
            int len = get_len(d, direct_cnt[d]);
            // 沿着 d 走 len 步, k = [1,2,...,len]
            // int nxt_i = i + dx[d] * len;
            // int nxt_j = j + dy[d] * len;
            // i + dx[d], y + dy[d]
            for(int k = 1; k <= len; ++k)
            {
                i += dx[d];
                j += dy[d];
                if(i < 0 || i >= R || j < 0 || j >= C)
                {
                    if(i < 0) up = true;
                    if(j < 0) left = true;
                    if(i >= R) down = true;
                    if(j >= C) right = true;
                    if(up && down && left && right)
                        return result;
                    continue;
                }
                result.push_back({i, j});
            }
            d = (d + 1) % 4;
        }
    }

private:
    // 0 东 1,3,5,...
    // 1 南 1,3,5,...
    // 2 西 2,4,6,...
    // 3 北 2,4,6,...
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    int get_len(int d, int cnt)
    {
        if(d == 0 || d == 1)
            return 2 * cnt - 1;
        else
            return 2 * cnt;
    }
};
