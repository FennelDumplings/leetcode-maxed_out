// prob542: 01 Matrix

/*
 * Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.
 * The distance between two adjacent cells is 1.
 */

/*
 * Example 1:
 * Input:
 * [[0,0,0],
 *  [0,1,0],
 *  [0,0,0]]
 * Output:
 * [[0,0,0],
 *  [0,1,0],
 *  [0,0,0]]
 * Example 2:
 * Input:
 * [[0,0,0],
 *  [0,1,0],
 *  [1,1,1]]
 * Output:
 * [[0,0,0],
 *  [0,1,0],
 *  [1,2,1]]
 */

/*
 * Note:
 * The number of elements of the given matrix will not exceed 10,000.
 * There are at least one 0 in the given matrix.
 * The cells are adjacent in only four directions: up, down, left and right.
 */

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        using PII = pair<int, int>;
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {1, -1, 0, 0};
        int n = matrix.size(), m = matrix[0].size();
        queue<PII> q;
        vector<vector<int> > dist(n, vector<int>(m, -1));
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(matrix[i][j] == 0)
                {
                    dist[i][j] = 0;
                    q.push(PII(i, j));
                }
            }
        }
        vector<PII> level_node;
        while(!q.empty())
        {
            level_node.clear();
            while(!q.empty())
            {
                level_node.push_back(q.front());
                q.pop();
            }
            for(PII node: level_node)
            {
                int i = node.first, j = node.second;
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d], y = j + dy[d];
                    if(x < 0 || x >= n || y < 0 || y >= m) continue;
                    if(dist[x][y] != -1) continue;
                    dist[x][y] = dist[i][j] + 1;
                    q.push(PII(x, y));
                }
            }
        }
        return dist;
    }
};
