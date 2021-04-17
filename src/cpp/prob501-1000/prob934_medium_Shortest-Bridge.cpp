// prob934: Shortest Bridge

/*
 * In a given 2D binary array A, there are two islands.  (An island is a 4-directionally connected group of 1s not connected to any other 1s.)
 * Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.
 * Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)
 */

/*
 * Example 1:
 * Input: A = [[0,1],[1,0]]
 * Output: 1
 * Example 2:
 * Input: A = [[0,1,0],[0,0,0],[0,0,1]]
 * Output: 2
 * Example 3:
 * Input: A = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
 * Output: 1
 */

/*
 * Constraints:
 * 2 <= A.length == A[0].length <= 100
 * A[i][j] == 0 or A[i][j] == 1
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestBridge(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        // 0: 海，1: 岛1，2: 岛2
        vector<vector<int> > color(n, vector<int>(m, 0));
        int id = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(A[i][j] == 0 || color[i][j] != 0) continue;
                ++id;
                bfs_dye(A, color, i, j, id);
            }
        }
        if(id < 2) return -1;
        return bfs(A, color);
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    using PII = pair<int, int>;

    int bfs(const vector<vector<int> >& A, vector<vector<int> >& color)
    {
        int n = A.size(), m = A[0].size();
        queue<PII> q;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
            {
                if(color[i][j] == 1)
                    q.push(PII(i, j));
            }
        vector<PII> level_nodes;
        int dist = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++dist;
            for(PII node: level_nodes)
            {
                for(int d = 0; d < 4; ++d)
                {
                    int x = node.first + dx[d];
                    int y = node.second + dy[d];
                    if(x < 0 || x >= n || y < 0 || y >= m)
                        continue;
                    if(color[x][y] == 1)
                        continue;
                    if(color[x][y] == 2)
                        return dist - 1;
                    color[x][y] = 1;
                    q.push(PII(x, y));
                }
            }
        }
        return -1;
    }

    void bfs_dye(const vector<vector<int> >& A, vector<vector<int> >& color, int i, int j, int id)
    {
        int n = A.size(), m = A[0].size();
        queue<PII> q;
        q.push(PII(i, j));
        color[i][j] = id;
        while(!q.empty())
        {
            PII node = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = node.first + dx[d];
                int y = node.second + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(A[x][y] == 0) continue;
                if(color[x][y] == id) continue;
                color[x][y] = id;
                q.push(PII(x, y));
            }
        }
    }
};
