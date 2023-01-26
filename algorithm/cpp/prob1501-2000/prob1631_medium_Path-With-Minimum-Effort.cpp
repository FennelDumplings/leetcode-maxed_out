// prob1631: Path With Minimum Effort

/*
 * https://leetcode-cn.com/problems/path-with-minimum-effort/
 */

#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct State
{
    int x, y, d;
    State(int x, int y, int d):x(x),y(y),d(d){}
};

struct HeapCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d > s2.d;
    }
};

class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size(), m = heights[0].size();
        priority_queue<State, vector<State>, HeapCmp> pq;
        pq.push(State(0, 0, 0));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(visited[cur.x][cur.y])
                continue;
            visited[cur.x][cur.y] = true;
            if(cur.x == n - 1 && cur.y == m - 1)
                return cur.d;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(visited[x][y])
                    continue;
                pq.push(State(x, y, max(abs(heights[cur.x][cur.y] - heights[x][y]), cur.d)));
            }
        }
        return -1;
    }
private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
};
