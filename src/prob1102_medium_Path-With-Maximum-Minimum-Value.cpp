// prob1102: Path With Maximum Minimum Value

/*
 * https://leetcode-cn.com/problems/path-with-maximum-minimum-value/
 */

#include <vector>
#include <queue>

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
        return s1.d < s2.d;
    }
};

class Solution {
public:
    int maximumMinimumPath(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        priority_queue<State, vector<State>, HeapCmp> pq;
        pq.push(State(0, 0, A[0][0]));
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(cur.x == n - 1 && cur.y == m - 1)
                return cur.d;
            if(visited[cur.x][cur.y])
                continue;
            visited[cur.x][cur.y] = true;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(visited[x][y])
                    continue;
                pq.push(State(x, y, min(cur.d, A[x][y])));
            }
        }
        return -1;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
};
