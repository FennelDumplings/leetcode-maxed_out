// prob407: Trapping Rain Water II

/*
 * https://leetcode-cn.com/problems/trapping-rain-water-ii/
 */

#include <queue>
#include <vector>

using namespace std;

struct Point
{
    int x, y, h;
    Point(int i, int j, int h):x(i),y(j),h(h){}
};

struct HeapCmp
{
    bool operator()(const Point& p1, const Point& p2) const
    {
        return p1.h > p2.h;
    }
};

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        if(heightMap.empty())
            return 0;
        int n = heightMap.size(), m = heightMap[0].size();
        if(n <= 2 || m <= 2)
            return 0;
        priority_queue<Point, vector<Point>, HeapCmp> pq;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i = 0; i < n; ++i)
        {
            pq.push(Point(i, 0, heightMap[i][0]));
            pq.push(Point(i, m - 1, heightMap[i][m - 1]));
            visited[i][0] = true;
            visited[i][m - 1] = true;
        }
        for(int j = 1; j < m - 1; ++j)
        {
            pq.push(Point(0, j, heightMap[0][j]));
            pq.push(Point(n - 1, j, heightMap[n - 1][j]));
            visited[0][j] = true;
            visited[n - 1][j] = true;
        }
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        int ans = 0;
        while(!pq.empty())
        {
            Point p = pq.top();
            pq.pop();
            for(int d = 0; d < 4; ++d)
            {
                int x = p.x + dx[d];
                int y = p.y + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(visited[x][y])
                    continue;
                visited[x][y] = true;
                int h = heightMap[x][y];
                if(h < p.h)
                {
                    ans += p.h - h;
                    pq.push(Point(x, y, p.h));
                }
                else
                    pq.push(Point(x, y, h));
            }
        }
        return ans;
    }
};
