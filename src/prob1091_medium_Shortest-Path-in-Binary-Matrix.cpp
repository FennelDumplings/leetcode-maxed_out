// prob1191: Shortest Path in Binary Matrix

/*
 * In an N by N square grid, each cell is either empty (0) or blocked (1).
 * A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:
 * Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
 * C_1 is at location (0, 0) (ie. has value grid[0][0])
 * C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
 * If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
 * Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int N = grid.size();
        if(N == 1 && grid[0][0] == 0) return 1;
        if(N == 1 && grid[0][0] == 1) return -1;
        if(grid[0][0] == 1) return -1;

        vector<vector<bool> > visited(N, vector<bool>(N, false));
        queue<PII> q;
        q.push(PII(0, 0));
        visited[0][0] = true;
        int dx[8] = {0, 0, 1, -1, 1, 1, -1, -1};
        int dy[8] = {1, -1, 0, 0, 1, -1, 1, -1};

        vector<PII> level_nodes;
        int result = 0;
        bool get_end = false;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            for(PII point: level_nodes)
            {
                if(point.first == N - 1 && point.second == N - 1)
                {
                    get_end = true;
                    break;
                }
                for(int d = 0; d < 8; ++d)
                {
                    PII nxt(point.first + dx[d], point.second + dy[d]);
                    if(_check(nxt, grid, visited))
                    {
                        q.push(nxt);
                        visited[nxt.first][nxt.second] = true;
                    }
                }
            }
            ++result;
            if(get_end)
                return result;
        }
        return -1;
    }

private:
    using PII = pair<int, int>;

    bool _check(const PII& nxt, const vector<vector<int> >& grid, vector<vector<bool> >& visited)
    {
        int N = grid.size();
        if(nxt.first < 0 || nxt.first >= N || nxt.second < 0 || nxt.second >= N) return false;
        return (!visited[nxt.first][nxt.second]) && (grid[nxt.first][nxt.second] == 0);
    }
};
