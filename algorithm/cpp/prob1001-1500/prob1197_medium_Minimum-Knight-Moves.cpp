// prob1197: Minimum Knight Moves

/*
 * https://leetcode-cn.com/problems/minimum-knight-moves/
 */

#include <vector>
#include <unordered_set>
#include <queue>
#include <cmath>

using namespace std;

// BFS 超时
/*
struct State
{
    int x;
    int y;
    int d;
    State(int x, int y, int d):x(x),y(y),d(d){}
    bool operator==(const State& s) const
    {
        return this -> x == s.x && this -> y == s.y;
    }
    bool operator<(const State& s) const
    {
        return (this -> x + this -> y) < (s.y + s.x);
    }
};

struct MyHash
{
    static constexpr int OFFSET = 305;
    int operator()(const State& s) const
    {
        return ((s.x + 305) * 305) + (s.y + 305);
    }
};

class Solution {
public:
    int minKnightMoves(int x, int y) {
        if(x == 0 && y == 0)
            return 0;
        unordered_set<State, MyHash> visited;
        visited.insert(State(0, 0, 0));
        queue<State> q;
        q.push(State(0, 0, 0));
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            for(int d = 0; d < 8; ++d)
            {
                int i = cur.x + dx[d], j = cur.y + dy[d];
                State nxt(i, j, cur.d + 1);
                if(visited.count(nxt) > 0)
                    continue;
                if(i == x && j == y)
                    return cur.d + 1;
                visited.insert(nxt);
                q.push(nxt);
            }
        }
        return -1;
    }

private:
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
};
*/

// 优先级队列 BFS
/*
 * 有优化，仍然超时
int h(int x, int y, int x0, int y0)
{
    return (abs(x - x0) + abs(y - y0)) / 3;
}

struct State
{
    int x;
    int y;
    int d;
    int h;
    State(int x, int y, int d):x(x),y(y),d(d),h(0){}
    bool operator==(const State& s) const
    {
        return this -> x == s.x && this -> y == s.y;
    }
};

struct HeapCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d + s1.h > s2.d + s2.h;
    }
};

struct MyHash
{
    static constexpr int OFFSET = 305;
    int operator()(const State& s) const
    {
        return ((s.x + 305) * 305) + (s.y + 305);
    }
};

class Solution {
public:
    int minKnightMoves(int x, int y) {
        unordered_set<State, MyHash> visited;
        State s(0, 0, 0);
        s.h = h(0, 0, x, y);
        priority_queue<State, vector<State>, HeapCmp> pq;
        pq.push(s);
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(cur.x == x && cur.y == y)
                return cur.d;
            if(visited.count(cur) > 0)
                continue;
            visited.insert(cur);
            for(int d = 0; d < 8; ++d)
            {
                int i = cur.x + dx[d], j = cur.y + dy[d];
                State nxt(i, j, cur.d + 1);
                nxt.h = h(i, j, x, y);
                if(visited.count(nxt) > 0)
                    continue;
                pq.push(nxt);
            }
        }
        return -1;
    }

private:
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
};
*/

// Astar 哈希表优化
/*
int h(int x, int y, int x0, int y0)
{
    return (abs(x - x0) + abs(y - y0)) / 3;
}

struct State
{
    int x;
    int y;
    int d;
    int h;
    State(int x, int y, int d):x(x),y(y),d(d),h(0){}
    bool operator==(const State& s) const
    {
        return this -> x == s.x && this -> y == s.y;
    }
};

struct HeapCmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d + s1.h > s2.d + s2.h;
    }
};

const int OFFSET = 305;

class Solution {
public:
    int minKnightMoves(int x, int y) {
        State s(0, 0, 0);
        s.h = h(0, 0, x, y);
        priority_queue<State, vector<State>, HeapCmp> pq;
        pq.push(s);
        visited.assign(610, vector<bool>(610, false));
        while(!pq.empty())
        {
            State cur = pq.top();
            pq.pop();
            if(cur.x == x && cur.y == y)
                return cur.d;
            if(visited[cur.x + OFFSET][cur.y + OFFSET])
                continue;
            visited[cur.x + OFFSET][cur.y + OFFSET] = true;
            for(int d = 0; d < 8; ++d)
            {
                int i = cur.x + dx[d], j = cur.y + dy[d];
                State nxt(i, j, cur.d + 1);
                nxt.h = h(i, j, x, y);
                if(visited[nxt.x + OFFSET][nxt.y + OFFSET])
                    continue;
                pq.push(nxt);
            }
        }
        return -1;
    }

private:
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    vector<vector<bool>> visited;
};
*/

// BFS 哈希表优化
/*
struct State
{
    int x;
    int y;
    int d;
    State(int x, int y, int d):x(x),y(y),d(d){}
};

const int OFFSET = 305;

class Solution {
public:
    int minKnightMoves(int x, int y) {
        if(x == 0 && y == 0)
            return 0;
        queue<State> q;
        q.push(State(0, 0, 0));
        visited.assign(610, vector<bool>(610, false));
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            for(int d = 0; d < 8; ++d)
            {
                int i = cur.x + dx[d], j = cur.y + dy[d];
                State nxt(i, j, cur.d + 1);
                if(visited[nxt.x + OFFSET][nxt.y + OFFSET])
                    continue;
                if(i == x && j == y)
                    return cur.d + 1;
                visited[nxt.x + OFFSET][nxt.y + OFFSET] = true;
                q.push(nxt);
            }
        }
        return -1;
    }

private:
    vector<vector<bool>> visited;
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
};
*/

#include <unordered_map>

struct State
{
    int x;
    int y;
    State(int x, int y):x(x),y(y){}
    bool operator==(const State& s) const
    {
        return this -> x == s.x && this -> y == s.y;
    }
    bool operator<(const State& s) const
    {
        return (this -> x + this -> y) < (s.y + s.x);
    }
};

struct MyHash
{
    static constexpr int OFFSET = 305;
    int operator()(const State& s) const
    {
        return ((s.x + 305) * 305) + (s.y + 305);
    }
};

class Solution {
public:
    int minKnightMoves(int x, int y) {
        return solve(abs(x), abs(y));
    }

private:
    unordered_map<State, int, MyHash> dp;
    int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

    int solve(int x, int y)
    {
        if(x == 0 && y == 0)
            return 0;
        if(x + y == 2)
            return 2;
        State s(x, y);
        if(dp.count(s) > 0)
            return dp[s];
        return dp[s] = 1 + min(solve(abs(x - 1), abs(y - 2)), solve(abs(x - 2), abs(y - 1)));
    }
};
