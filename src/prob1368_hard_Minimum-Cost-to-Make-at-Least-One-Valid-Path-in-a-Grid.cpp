// prob1368: Minimum Cost to Make at Least One Valid Path in a Grid

/*
 * https://leetcode-cn.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
 */

#include <vector>
#include <deque>

using namespace std;

struct State
{
    int x, y;
    int d;
    State(int x, int y, int d):x(x),y(y),d(d){}
};

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        deque<State> deq;
        deq.push_back(State(0, 0, 0));
        while(!deq.empty())
        {
            State cur = deq.back();
            deq.pop_back();
            int i = cur.x;
            int j = cur.y;
            if(i == n - 1 && j == m - 1)
                return cur.d;
            // i, j 位置已经出过队后，就不让再进队了
            visited[i][j] = true;
            for(int d = 0; d < 4; ++d)
            {
                int x = i + dx[d];
                int y = j + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m)
                    continue;
                if(visited[x][y])
                    continue;
                if(d == grid[i][j] - 1)
                    deq.push_back(State(x, y, cur.d));
                else
                    deq.push_front(State(x, y, cur.d + 1));
            }
        }
        return -1;
    }

private:
    // 右左下上
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
};

