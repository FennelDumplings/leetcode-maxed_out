// prob1162: As Far from Land as Possible



#include <vector>
#include <queue>

using namespace std;

// 多源BFS
class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int N = grid.size();
        using PII = pair<int, int>;
        int result = -1;
        vector<vector<bool> > visited(N, vector<bool>(N, false));
        queue<PII> q;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if(grid[i][j] == 1)
                    q.push(PII(i, j));
        vector<PII> level_nodes;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        while(!q.empty())
        {
            level_nodes.clear();
            ++result;
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(PII node: level_nodes)
            {
                for(int d = 0; d < 4; ++d)
                {
                    int x = node.first + dx[d];
                    int y = node.second + dy[d];
                    if(x < 0 || x >= N || y < 0 || y >= N || grid[x][y] == 1 || visited[x][y])
                        continue;
                    PII nxt(x, y);
                    q.push(nxt);
                    visited[x][y] = true;
                }
            }
        }
        if(result <= 0) return -1;
        return result;
    }
};
