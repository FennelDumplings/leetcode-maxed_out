// prob317: Shortest Distance from All Buildings

/*
 * https://leetcode-cn.com/problems/shortest-distance-from-all-buildings/
 */

#include <vector>
#include <queue>

using namespace std;

// 多源 BFS，染色
struct Point
{
    int i, j;
    int c; // 颜色
    int d; // 与 c 的源的距离
    Point(int i, int j, int c, int d):i(i),j(j),c(c),d(d){}
};

struct State
{
    vector<int> d; // d[c] := 到颜色为 c 的建筑物的距离, -1 表示未触达
    int cnt; // 已经触达的建筑数目
    int sum; // 已经触达的建筑的距离和
    State(int cnt=0)
    {
        sum = 0;
        this -> cnt = 0;
        d.assign(cnt, -1);
    }
};

class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int C = 0; // 建筑物总数
        queue<Point> q;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(grid[i][j] == 1)
                    q.push(Point(i, j, C++, 0));
            }
        vector<vector<State>> states(n, vector<State>(m, State(C))); // 各个点的状态

        int ans = n * m * C;
        while(!q.empty())
        {
            Point p = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = p.i + dx[d], y = p.j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(grid[x][y] != 0)
                    continue;
                if(states[x][y].d[p.c] != -1)
                    continue;
                ++states[x][y].cnt;
                states[x][y].d[p.c] = p.d + 1;
                states[x][y].sum += p.d + 1;
                if(states[x][y].cnt == C)
                    ans = min(ans, states[x][y].sum);
                q.push(Point(x, y, p.c, p.d + 1));
            }
        }
        if(ans == n * m * C)
            return -1;
        return ans;
    }

private:
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
};
