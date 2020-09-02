
#include <vector>

using namespace std;

class Solution {
public:
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        vector<vector<int>> dist(n, vector<int>(m, 0));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(visited[i][j])
                    continue;
                visited[i][j] = true;
                dist[i][j] = 1;
                if(dfs(grid, i, j, visited, dist))
                    return true;
            }
        return false;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    bool dfs(const vector<vector<char>>& grid, int i, int j, vector<vector<bool>>& visited, vector<vector<int>>& dist)
    {
        int n = grid.size(), m = grid[0].size();
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m)
                continue;
            if(grid[x][y] != grid[i][j])
                continue;
            if(visited[x][y])
            {
                if(dist[i][j] - dist[x][y] + 1 >= 4)
                    return true;
                continue;
            }
            visited[x][y] = true;
            dist[x][y] = dist[i][j] + 1;
            if(dfs(grid, x, y, visited, dist))
                return true;
        }
        return false;
    }
};



[["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
[["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
[["a","b","b"],["b","z","b"],["b","b","a"]]
[["c","a","d"],["a","a","a"],["a","a","d"],["a","c","d"],["a","b","c"]]
[["b","a","c"],["c","a","c"],["d","d","c"],["b","c","c"]]
