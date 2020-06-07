// prob829: Making A Large Island

/*
 * In a 2D grid of 0s and 1s, we change at most one 0 to a 1.
 * After, what is the size of the largest island? (An island is a 4-directionally connected group of 1s).
 */

/*
 * Example 1:
 * Input: [[1, 0], [0, 1]]
 * Output: 3
 * Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
 * Example 2:
 * Input: [[1, 1], [1, 0]]
 * Output: 4
 * Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.
 * Example 3:
 * Input: [[1, 1], [1, 1]]
 * Output: 4
 * Explanation: Can't change any 0 to 1, only one island with area = 4.
 */

/*
 * Notes:
 * 1 <= grid.length = grid[0].length <= 50.
 * 0 <= grid[i][j] <= 1.
 */

#include <vector>
#include <queue>

using namespace std;

using PII = pair<int, int>;

struct Inland
{
    int area;
    vector<PII> borders;
    Inland(int area):area(area)
    {
        borders = vector<PII>();
    }
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<Inland> inlands; // color -> inlands[color - 1]
        vector<vector<int> > visited(n, vector<int>(m, 0));
        int color = 1;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 0) continue;
                if(visited[i][j] != 0) continue;
                bfs(grid, i, j, visited, color, inlands);
                ++color;
            }
        int color_iter = 1;
        int n_inland = inlands.size();
        if(n_inland == 0) return 1;
        int result = 0;
        vector<bool> flags(n_inland, false);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(visited[i][j] == color_iter)
                {
                    if(inlands[color_iter - 1].borders.empty())
                    {
                        return inlands[color_iter - 1].area;
                    }
                    int area = inlands[color_iter - 1].area;
                    int max_nxt_area = 1;
                    for(PII border: inlands[color_iter - 1].borders)
                    {
                        int nxt_area = 1;
                        flags.assign(n_inland, false);
                        for(int d = 0; d < 4; ++d)
                        {
                            int x = border.first + dx[d];
                            int y = border.second + dy[d];
                            if(x < 0 || x >= n || y < 0 || y >= m) continue;
                            if(grid[x][y] == 0) continue;
                            if(visited[x][y] > color_iter && !flags[visited[x][y] - 1])
                            {
                                flags[visited[x][y] - 1] = true;
                                nxt_area += inlands[visited[x][y] - 1].area;
                            }
                        }
                        max_nxt_area = max(max_nxt_area, nxt_area);
                    }
                    area += max_nxt_area;
                    result = max(result, area);
                    ++color_iter;
                }
            }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    void bfs(const vector<vector<int> >& grid, int i, int j, vector<vector<int> >& visited, int color, vector<Inland>& inlands)
    {
        inlands.push_back(Inland(0));
        Inland& inland = inlands[(int)inlands.size() - 1];
        int n = grid.size(), m = grid[0].size();
        queue<PII> q;
        q.push(PII(i, j));
        visited[i][j] = color;
        while(!q.empty())
        {
            PII cur = q.front();
            q.pop();
            ++inland.area;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.first + dx[d];
                int y = cur.second + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(grid[x][y] == 0)
                {
                    inland.borders.push_back(PII(x, y));
                    continue;
                }
                if(visited[x][y] != 0) continue;
                visited[x][y] = color;
                q.push(PII(x, y));
            }
        }
    }
};
