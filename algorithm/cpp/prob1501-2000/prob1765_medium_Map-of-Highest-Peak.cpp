#include <vector>
#include <queue>

using namespace std;

struct Point
{
    int x, y;
    Point(){}
    Point(int x, int y):x(x),y(y){}
};

class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = isWater.size();
        int m = isWater[0].size();
        queue<Point> q;
        vector<vector<int>> result(n, vector<int>(m, -1));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(isWater[i][j] == 1)
                {
                    result[i][j] = 0;
                    q.push(Point(i, j));
                }
            }
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};
        while(!q.empty())
        {
            Point cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                Point nxt(cur.x + dx[d], cur.y + dy[d]);
                if(nxt.x < 0 || nxt.x >= n || nxt.y < 0 || nxt.y >= m)
                    continue;
                if(result[nxt.x][nxt.y] != -1)
                    continue;
                result[nxt.x][nxt.y] = result[cur.x][cur.y] + 1;
                q.push(nxt);
            }
        }
        return result;
    }
};
