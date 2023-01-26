// prob773: Sliding Puzzle

/*
 * https://leetcode-cn.com/problems/sliding-puzzle/
 */

#include <vector>
#include <cmath>
#include <queue>

using namespace std;


const int N = 2, M = 3;

void change_zero(vector<int>& s)
{
    // 将 s 中的 0 交换至右下角
    int zero_idx = -1;
    for(int i = 0; i < N * M; ++i)
    {
        if(s[i] == 0)
        {
            zero_idx = i;
            break;
        }
    }
    while((zero_idx % M) < M - 1)
    {

        swap(s[zero_idx + 1], s[zero_idx]);
        ++zero_idx;
    }
    while(zero_idx / M < N - 1)
    {
        swap(s[zero_idx + M], s[zero_idx]);
        zero_idx += M;
    }
}

bool check(vector<int> s, vector<int> t)
{
    change_zero(s);
    vector<int> idx(6, 0);
    for(int i = 0; i < 6; ++i)
        idx[s[i]] = i;
    int swap_cnt = 0;
    for(int i = 0; i < 5; ++i)
    {
        if(s[i] == t[i])
            continue;
        int a = s[i];
        int p = idx[t[i]];
        swap(s[i], s[idx[t[i]]]);
        idx[t[i]] = i;
        idx[a] = p;
        ++swap_cnt;
    }
    return (swap_cnt & 1) == 0;
}

int fac(int N)
{
    int ans = 1;
    for(int i = 2; i <= N; ++i)
        ans *= i;
    return ans;
}

int _idx(int x, int y)
{
    return x * M + y;
}

// ----------------------------------------------------------------

// DFS
class Solution_2 {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int start = 0;
        vector<int> start_vec(6, -1);
        int zero_idx = -1;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
            {
                start *= 10;
                start += board[i][j];
                start_vec[_idx(i, j)] = board[i][j];
                if(board[i][j] == 0)
                    zero_idx = _idx(i, j);
            }
        if(!check(start_vec, vector<int>{1,2,3,4,5,0}))
            return -1;
        const int n_states = fac(N * M); // 6! 种状态
        int ans = n_states;
        int end = 123450;
        visited = vector<bool>(543211, false);
        visited[start] = true;
        dfs(start, end, zero_idx, 0, ans);
        if(ans == n_states)
            return -1;
        return ans;
    }

private:
    // 右，左，下，上
    int d[4] = {1, -1, M, -M};
    vector<bool> visited;

    int _swap(int s, int zero_idx, int nxt_zero_idx)
    {
        int digit = (s / (int)pow(10, 5 - nxt_zero_idx)) % 10;
        int ans = s - digit * pow(10, 5 - nxt_zero_idx);
        ans += digit * pow(10, 5 - zero_idx);
        return ans;
    }

    void dfs(int s, const int t, int zero_idx, int deep, int& ans)
    {
        if(deep >= ans)
            return;
        if(s == t)
        {
            ans = min(ans, deep);
            return;
        }
        for(int i = 0; i < 4; ++i)
        {
            int nxt_zero_idx = zero_idx + d[i];
            if(nxt_zero_idx >= M * N || nxt_zero_idx < 0 || (nxt_zero_idx / M != zero_idx / M && nxt_zero_idx % M != zero_idx % M))
                continue;
            // s -> 交换 nxt_zero_idx 和 zero_idx 位置的数字 -> s'
            int nxt = _swap(s, zero_idx, nxt_zero_idx);
            if(visited[nxt])
                continue;
            visited[nxt] = true;
            dfs(nxt, t, nxt_zero_idx, deep + 1, ans);
            visited[nxt] = false;
        }
    }
};

// ------------------------

// BFS
class Solution_3 {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int start = 0;
        vector<int> start_vec(6, -1);
        int zero_idx = -1;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
            {
                start *= 10;
                start += board[i][j];
                start_vec[_idx(i, j)] = board[i][j];
                if(board[i][j] == 0)
                    zero_idx = _idx(i, j);
            }
        if(!check(start_vec, vector<int>{1,2,3,4,5,0}))
            return -1;
        int end = 123450;
        State s(start, 0, zero_idx);
        return bfs(s, end);
    }

private:
    // 右，左，下，上
    int d[4] = {1, -1, M, -M};

    struct State
    {
        int s;
        int d;
        int zero_idx;
        State(int s, int d, int i):s(s), d(d),zero_idx(i){}
    };

    int bfs(State s, int t)
    {
        queue<State> q;
        q.push(s);
        vector<bool> visited(543211, false);
        visited[s.s] = true;
        while(!q.empty())
        {
            State cur = q.front();
            q.pop();
            if(cur.s == t)
                return cur.d;
            for(int i = 0; i < 4; ++i)
            {
                int nxt_zero_idx = cur.zero_idx + d[i];
                if(nxt_zero_idx >= M * N || nxt_zero_idx < 0 || (nxt_zero_idx / M != cur.zero_idx / M && nxt_zero_idx % M != cur.zero_idx % M))
                    continue;
                int nxt_s = _swap(cur.s, cur.zero_idx, nxt_zero_idx);
                if(visited[nxt_s])
                    continue;
                visited[nxt_s] = true;
                State nxt(nxt_s, cur.d + 1, nxt_zero_idx);
                q.push(nxt);
            }
        }
        return -1;
    }

    int _swap(int s, int zero_idx, int nxt_zero_idx)
    {
        int digit = (s / (int)pow(10, 5 - nxt_zero_idx)) % 10;
        int ans = s - digit * pow(10, 5 - nxt_zero_idx);
        ans += digit * pow(10, 5 - zero_idx);
        return ans;
    }
};

// Astar
class Solution_4 {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int start = 0;
        vector<int> start_vec(6, -1);
        int zero_idx = -1;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
            {
                start *= 10;
                start += board[i][j];
                start_vec[_idx(i, j)] = board[i][j];
                if(board[i][j] == 0)
                    zero_idx = _idx(i, j);
            }
        if(!check(start_vec, vector<int>{1,2,3,4,5,0}))
            return -1;
        int end = 123450;
        State s(start, 0, zero_idx, h(start, end));
        return bfs(s, end);
    }

private:
    // 右，左，下，上
    int d[4] = {1, -1, M, -M};

    struct State
    {
        int s;
        int d;
        int zero_idx;
        int h;
        State(int s, int d, int i, int h):s(s), d(d),zero_idx(i),h(h){}
    };

    struct Cmp
    {
        bool operator()(const State& s1, const State& s2) const
        {
            return s1.d + s1.h > s2.d + s2.h;
        }
    };

    int bfs(State s, int t)
    {
        priority_queue<State, vector<State>, Cmp> q;
        q.push(s);
        vector<bool> visited(543211, false);
        while(!q.empty())
        {
            State cur = q.top();
            q.pop();
            if(cur.s == t)
                return cur.d;
            if(visited[cur.s])
                continue;
            visited[cur.s] = true;
            for(int i = 0; i < 4; ++i)
            {
                int nxt_zero_idx = cur.zero_idx + d[i];
                if(nxt_zero_idx >= M * N || nxt_zero_idx < 0 || (nxt_zero_idx / M != cur.zero_idx / M && nxt_zero_idx % M != cur.zero_idx % M))
                    continue;
                int nxt_s = _swap(cur.s, cur.zero_idx, nxt_zero_idx);
                if(visited[nxt_s])
                    continue;
                State nxt(nxt_s, cur.d + 1, nxt_zero_idx, h(nxt_s, t));
                q.push(nxt);
            }
        }
        return -1;
    }

    int h(int s, int t)
    {
        int ans = 0;
        for(int i = 0; i < 6; ++i)
        {
            int digit = (s / (int)pow(10, i)) % 10;
            if(digit == 0)
                continue;
            // i 要移动到 v
            int v = -1;
            for(int j = 0; j < 6; ++j)
            {
                int digit2 = (t / (int)pow(10, j)) % 10;
                if(digit2 == digit)
                {
                    v = j;
                    break;
                }
            }
            ans += (abs(v / 3 - i / 3) + abs(v % 3 - i % 3));
        }
        return ans / 2;
    }

    int _swap(int s, int zero_idx, int nxt_zero_idx)
    {
        int digit = (s / (int)pow(10, 5 - nxt_zero_idx)) % 10;
        int ans = s - digit * pow(10, 5 - nxt_zero_idx);
        ans += digit * pow(10, 5 - zero_idx);
        return ans;
    }
};


// ID
class Solution_5 {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int start = 0;
        vector<int> start_vec(6, -1);
        int zero_idx = -1;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
            {
                start *= 10;
                start += board[i][j];
                start_vec[_idx(i, j)] = board[i][j];
                if(board[i][j] == 0)
                    zero_idx = _idx(i, j);
            }
        if(!check(start_vec, vector<int>{1,2,3,4,5,0}))
            return -1;
        // 确定有解
        int end = 123450;
        visited = vector<bool>(543211, false);
        visited[start] = true;
        int depth = 0;
        while(!dfs(start, end, zero_idx, 0, depth))
        {
            ++depth;
            visited.assign(543211, false);
            visited[start] = true;
        }
        return depth;
    }

private:
    // 右，左，下，上
    int d[4] = {1, -1, M, -M};
    vector<bool> visited;

    int _swap(int s, int zero_idx, int nxt_zero_idx)
    {
        int digit = (s / (int)pow(10, 5 - nxt_zero_idx)) % 10;
        int ans = s - digit * pow(10, 5 - nxt_zero_idx);
        ans += digit * pow(10, 5 - zero_idx);
        return ans;
    }

    bool dfs(int s, const int t, int zero_idx, int deep, const int max_deep)
    {
        if(deep > max_deep)
            return false;
        if(s == t)
        {
            return true;
        }
        for(int i = 0; i < 4; ++i)
        {
            int nxt_zero_idx = zero_idx + d[i];
            if(nxt_zero_idx >= M * N || nxt_zero_idx < 0 || (nxt_zero_idx / M != zero_idx / M && nxt_zero_idx % M != zero_idx % M))
                continue;
            // s -> 交换 nxt_zero_idx 和 zero_idx 位置的数字 -> s'
            int nxt = _swap(s, zero_idx, nxt_zero_idx);
            if(visited[nxt])
                continue;
            visited[nxt] = true;
            if(dfs(nxt, t, nxt_zero_idx, deep + 1, max_deep))
                return true;
            visited[nxt] = false;
        }
        return false;
    }
};

// IDAstar
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int start = 0;
        vector<int> start_vec(6, -1);
        int zero_idx = -1;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < M; ++j)
            {
                start *= 10;
                start += board[i][j];
                start_vec[_idx(i, j)] = board[i][j];
                if(board[i][j] == 0)
                    zero_idx = _idx(i, j);
            }
        if(!check(start_vec, vector<int>{1,2,3,4,5,0}))
            return -1;
        // 确定有解
        int end = 123450;
        visited = vector<bool>(543211, false);
        visited[start] = true;
        int depth = 0;
        while(!dfs(start, end, zero_idx, 0, depth))
        {
            ++depth;
            visited.assign(543211, false);
            visited[start] = true;
        }
        return depth;
    }

private:
    // 右，左，下，上
    int d[4] = {1, -1, M, -M};
    vector<bool> visited;

    int _swap(int s, int zero_idx, int nxt_zero_idx)
    {
        int digit = (s / (int)pow(10, 5 - nxt_zero_idx)) % 10;
        int ans = s - digit * pow(10, 5 - nxt_zero_idx);
        ans += digit * pow(10, 5 - zero_idx);
        return ans;
    }

    int h(int s, int t)
    {
        int ans = 0;
        for(int i = 0; i < 6; ++i)
        {
            int digit = (s / (int)pow(10, i)) % 10;
            if(digit == 0)
                continue;
            // i 要移动到 v
            int v = -1;
            for(int j = 0; j < 6; ++j)
            {
                int digit2 = (t / (int)pow(10, j)) % 10;
                if(digit2 == digit)
                {
                    v = j;
                    break;
                }
            }
            ans += (abs(v / 3 - i / 3) + abs(v % 3 - i % 3));
        }
        return ans / 2;
    }

    bool dfs(int s, const int t, int zero_idx, int deep, const int max_deep)
    {
        if(deep + h(s, t) > max_deep)
            return false;
        if(s == t)
        {
            return true;
        }
        for(int i = 0; i < 4; ++i)
        {
            int nxt_zero_idx = zero_idx + d[i];
            if(nxt_zero_idx >= M * N || nxt_zero_idx < 0 || (nxt_zero_idx / M != zero_idx / M && nxt_zero_idx % M != zero_idx % M))
                continue;
            // s -> 交换 nxt_zero_idx 和 zero_idx 位置的数字 -> s'
            int nxt = _swap(s, zero_idx, nxt_zero_idx);
            if(visited[nxt])
                continue;
            visited[nxt] = true;
            if(dfs(nxt, t, nxt_zero_idx, deep + 1, max_deep))
                return true;
            visited[nxt] = false;
        }
        return false;
    }
};
