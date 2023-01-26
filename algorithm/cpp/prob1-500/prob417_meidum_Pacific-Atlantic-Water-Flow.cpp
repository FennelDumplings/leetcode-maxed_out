// prob417: Pacific Atlantic Water Flow

/*
 * https://leetcode-cn.com/problems/pacific-atlantic-water-flow/
 */

#include <vector>
#include <queue>

using namespace std;

// 多源 BFS，染色
struct Point
{
    int i, j;
    Point(int i, int j):i(i),j(j){}
};

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
        if(matrix.empty()) return {};
        int n = matrix.size(), m = matrix[0].size();
        queue<Point> q;
        // 各个点的颜色, 0 表示未访问过，1 表示与太平洋相连
        vector<vector<int>> color(n, vector<int>(m, 0));
        for(int i = 0; i < n; ++i)
        {
            color[i][0] = 1;
            q.push(Point(i, 0));
        }
        for(int j = 0; j < m; ++j)
        {
            color[0][j] = 1;
            q.push(Point(0, j));
        }
        while(!q.empty())
        {
            Point p = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = p.i + dx[d], y = p.j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(matrix[x][y] < matrix[p.i][p.j])
                    continue;
                if(color[x][y] == 1)
                    continue;
                color[x][y] = 1;
                q.push(Point(x, y));
            }
        }
        vector<vector<int>> result;
        for(int i = 0; i < n; ++i)
        {
            if(color[i][m - 1] == 1)
                result.push_back({i, m - 1});
            color[i][m - 1] = 2;
            q.push(Point(i, m - 1));
        }
        for(int j = 0; j < m; ++j)
        {
            if(color[n - 1][j] == 1)
                result.push_back({n - 1, j});
            color[n - 1][j] = 2;
            q.push(Point(n - 1, j));
        }
        while(!q.empty())
        {
            Point p = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = p.i + dx[d], y = p.j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(matrix[x][y] < matrix[p.i][p.j])
                    continue;
                if(color[x][y] == 2)
                    continue;
                if(color[x][y] == 1)
                    result.push_back({x, y});
                color[x][y] = 2;
                q.push(Point(x, y));
            }
        }
        return result;
    }

private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};
