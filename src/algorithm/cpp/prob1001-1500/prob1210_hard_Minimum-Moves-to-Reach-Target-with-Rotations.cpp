// prob1210: Minimum Moves to Reach Target with Rotations

/*
 * https://leetcode-cn.com/problems/minimum-moves-to-reach-target-with-rotations/
 */

#include <vector>
#include <queue>

using namespace std;

/*
struct State
{
    int x, y; // 蛇尾位置
    int ori; // 0: 横, 1: 竖
    int d;
    State(int x, int y, bool ori, int d):x(x),y(y),ori(ori),d(d){}
};

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        State S(0, 0, 0, 0);
        queue<State> q;
        q.push(S);
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(n, vector<bool>(2, false)));
        visited[0][0][0] = true;
        int k = 0;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            vector<State> nxts = get_nxt(grid, cur);
            for(State &nxt: nxts)
            {
                if(check(nxt, n - 1, m - 1))
                    return nxt.d;
                if(visited[nxt.x][nxt.y][nxt.ori])
                    continue;
                visited[nxt.x][nxt.y][nxt.ori] = true;
                q.push(nxt);
            }
            ++k;
        }
        return -1;
    }

private:
    bool check(const State& s, int x0, int y0)
    {
        if(s.ori == 1)
            return false;
        int x1, y1;
        x1 = s.x;
        y1 = s.y + 1;
        return x1 == x0 && y1 == y0;
    }

    vector<State> get_nxt(const vector<vector<int>>& grid, const State& s)
    {
        int n = grid.size(), m = grid[0].size();
        int x1 = s.x, y1 = s.y;
        vector<State> result;
        if(s.ori == 0)
        {
            // 横着
            // 向右平移
            if(y1 + 2 < m && grid[x1][y1 + 2] == 0)
                result.emplace_back(x1, y1 + 1, s.ori, s.d + 1);
            // 向下平移
            if(x1 + 1 < n && grid[x1 + 1][y1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1 + 1, y1, s.ori, s.d + 1);
            // 顺时针旋转
            if(x1 + 1 < n && grid[x1 + 1][y1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1, s.ori ^ 1, s.d + 1);
        }
        else
        {
            // 竖着
            // 向右平移
            if(y1 + 1 < m && grid[x1][y1 + 1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1 + 1, s.ori, s.d + 1);
            // 向下平移
            if(x1 + 2 < n && grid[x1 + 2][y1] == 0)
                result.emplace_back(x1 + 1, y1, s.ori, s.d + 1);
            // 逆时针旋转
            if(y1 + 1 < m && grid[x1][y1 + 1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1, s.ori ^ 1, s.d + 1);
        }
        return result;
    }
};
struct State
{
    int x, y; // 蛇尾位置
    int ori; // 0: 横, 1: 竖
    int d;
    State(int x, int y, bool ori, int d):x(x),y(y),ori(ori),d(d){}
};

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        State S(0, 0, 0, 0);
        queue<State> q;
        q.push(S);
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(n, vector<bool>(2, false)));
        visited[0][0][0] = true;
        int k = 0;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            vector<State> nxts = get_nxt(grid, cur);
            for(State &nxt: nxts)
            {
                if(check(nxt, n - 1, m - 1))
                    return nxt.d;
                if(visited[nxt.x][nxt.y][nxt.ori])
                    continue;
                visited[nxt.x][nxt.y][nxt.ori] = true;
                q.push(nxt);
            }
            ++k;
        }
        return -1;
    }

private:
    bool check(const State& s, int x0, int y0)
    {
        if(s.ori == 1)
            return false;
        int x1, y1;
        x1 = s.x;
        y1 = s.y + 1;
        return x1 == x0 && y1 == y0;
    }

    vector<State> get_nxt(const vector<vector<int>>& grid, const State& s)
    {
        int n = grid.size(), m = grid[0].size();
        int x1 = s.x, y1 = s.y;
        vector<State> result;
        if(s.ori == 0)
        {
            // 横着
            // 向右平移
            if(y1 + 2 < m && grid[x1][y1 + 2] == 0)
                result.emplace_back(x1, y1 + 1, s.ori, s.d + 1);
            // 向下平移
            if(x1 + 1 < n && grid[x1 + 1][y1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1 + 1, y1, s.ori, s.d + 1);
            // 顺时针旋转
            if(x1 + 1 < n && grid[x1 + 1][y1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1, s.ori ^ 1, s.d + 1);
        }
        else
        {
            // 竖着
            // 向右平移
            if(y1 + 1 < m && grid[x1][y1 + 1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1 + 1, s.ori, s.d + 1);
            // 向下平移
            if(x1 + 2 < n && grid[x1 + 2][y1] == 0)
                result.emplace_back(x1 + 1, y1, s.ori, s.d + 1);
            // 逆时针旋转
            if(y1 + 1 < m && grid[x1][y1 + 1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1, s.ori ^ 1, s.d + 1);
        }
        return result;
    }
};
*/

// Astar
#include <cmath>

struct State
{
    int x, y; // 蛇尾位置
    int ori; // 0: 横, 1: 竖
    int d;
    int h;
    State(int x, int y, bool ori, int d):x(x),y(y),ori(ori),d(d){}
    bool operator<(const State& s) const
    {
        return d + h > s.d + s.h;
    }
};

int h(int x, int y, int x0, int y0)
{
    return abs(x - x0) + abs(y - y0);
}

class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        State S(0, 0, 0, 0);
        S.h = h(0, 0, n - 1, m - 2);
        priority_queue<State, vector<State>> pq;
        pq.push(S);
        vector<vector<vector<bool>>> visited(n, vector<vector<bool>>(n, vector<bool>(2, false)));
        int k = 0;
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(visited[cur.x][cur.y][cur.ori])
                continue;
            visited[cur.x][cur.y][cur.ori] = true;
            vector<State> nxts = get_nxt(grid, cur);
            for(State &nxt: nxts)
            {
                if(check(nxt, n - 1, m - 1))
                    return nxt.d;
                if(visited[nxt.x][nxt.y][nxt.ori])
                    continue;
                nxt.h = h(nxt.x, nxt.y, n - 1, m - 2);
                pq.push(nxt);
            }
            ++k;
        }
        return -1;
    }

private:
    bool check(const State& s, int x0, int y0)
    {
        if(s.ori == 1)
            return false;
        int x1, y1;
        x1 = s.x;
        y1 = s.y + 1;
        return x1 == x0 && y1 == y0;
    }

    vector<State> get_nxt(const vector<vector<int>>& grid, const State& s)
    {
        int n = grid.size(), m = grid[0].size();
        int x1 = s.x, y1 = s.y;
        vector<State> result;
        if(s.ori == 0)
        {
            // 横着
            // 向右平移
            if(y1 + 2 < m && grid[x1][y1 + 2] == 0)
                result.emplace_back(x1, y1 + 1, s.ori, s.d + 1);
            // 向下平移
            if(x1 + 1 < n && grid[x1 + 1][y1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1 + 1, y1, s.ori, s.d + 1);
            // 顺时针旋转
            if(x1 + 1 < n && grid[x1 + 1][y1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1, s.ori ^ 1, s.d + 1);
        }
        else
        {
            // 竖着
            // 向右平移
            if(y1 + 1 < m && grid[x1][y1 + 1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1 + 1, s.ori, s.d + 1);
            // 向下平移
            if(x1 + 2 < n && grid[x1 + 2][y1] == 0)
                result.emplace_back(x1 + 1, y1, s.ori, s.d + 1);
            // 逆时针旋转
            if(y1 + 1 < m && grid[x1][y1 + 1] == 0 && grid[x1 + 1][y1 + 1] == 0)
                result.emplace_back(x1, y1, s.ori ^ 1, s.d + 1);
        }
        return result;
    }
};
