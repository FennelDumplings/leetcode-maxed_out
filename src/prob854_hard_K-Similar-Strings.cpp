// prob854: K-Similar Strings

/*
 * https://leetcode-cn.com/problems/k-similar-strings/
 */

#include <string>
#include <unordered_map>
#include <queue>
#include <climits>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

// BFS
class Solution_2 {
private:
    struct State
    {
        string s;
        int d;
        State(string& s, int d):s(s),d(d){}
    };

public:
    int kSimilarity(string A, string B) {
        int n = A.size();
        queue<State> q;
        q.push(State(A, 0));
        unordered_set<string> visited;
        visited.insert(A);
        while(!q.empty())
        {
            State s = q.front();
            q.pop();
            if(s.s == B)
                return s.d;
            string &son = s.s;
            int i = 0;
            while(son[i] == B[i])
                ++i;
            // son[i] != B[i] 的位置
            // 从 son[i+1..n-1] 找到所有 B[i] 位置进行交换
            for(int j = i + 1; j < n; ++j)
            {
                if(son[j] == B[i])
                {
                    swap(son[i], son[j]);
                    if(visited.count(son) == 0)
                    {
                        visited.insert(son);
                        q.push(State(son, s.d + 1));
                    }
                    swap(son[i], son[j]);
                }
            }
        }
        return -1;
    }
};

// 贪心第取最小环
struct MyHash
{
    int operator()(const vector<int>& cycle) const
    {
        int ans = 0;
        for(int i: cycle)
        {
            ans *= 10;
            ans += i;
        }
        return ans;
    }
};

struct MyCmp
{
    bool operator()(const vector<int>& cycle1, const vector<int>& cycle2) const
    {
        int l = cycle1.size();
        int i = 0;
        int j = 0;
        while(j < l && cycle2[j] != cycle1[i])
            ++j;
        for(int k = 0; k < l; ++k)
            if(cycle1[(i + k) % l] != cycle2[(j + k) % l])
                return false;
        return true;
    }
};

class Solution_3 {
public:
    int kSimilarity(string A, string B) {
        // D[i][j] := i -> j 的边的条数，并在寻找最小环，以及后续的删边中动态维护
        // 经过若干论找最小环，使得所有 i != j 的 D[i][j] 均变为 0
        vector<vector<int>> D(N, vector<int>(N, 0));
        int n = A.size();
        for(int i = 0; i < n; ++i)
            if(A[i] != B[i])
                ++D[A[i] - 'a'][B[i] - 'a'];
        check(D);
        int ans = 0;
        vector<vector<int>> adj;
        bool flag = true;
        do{
            adj.assign(N, vector<int>(N, INT_MAX / 2));
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j)
                {
                    adj[i][i] = 0;
                    if(i != j && D[i][j] > 0)
                        adj[i][j] = 1;
                }
            unordered_set<vector<int>, MyHash, MyCmp> cycles_set = find_cycle(adj);
            flag = !cycles_set.empty();
            if(flag)
            {
                vector<vector<int>> cycles(cycles_set.begin(), cycles_set.end());
                vector<int> cycle = get_cycle(cycles);
                int l = cycle.size();
                ans += l - 1;
                --D[cycle[l - 1]][cycle[0]];
                for(int i = 0; i < l - 1; ++i)
                {
                    --D[cycle[i]][cycle[i + 1]];
                }
            }
        }while(flag);
        ans += check(D);
        return ans;
    }

private:
    const int N = 6;

    vector<int> get_cycle(vector<vector<int>>& cycles)
    {
        int m = cycles.size();
        vector<int> scores(m, 0);
        int l = cycles[0].size();
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                if(i == j) continue;
                for(int k = 0; k < l; ++k)
                    if(cycles[i][k] == cycles[j][k] && cycles[i][(k + 1) % l] == cycles[j][(k + 1) % l])
                    {
                        ++scores[i];
                        ++scores[j];
                    }
            }
        }
        int min_score = m;
        int idx = m;
        for(int i = 0; i < m; ++i)
        {
            if(min_score > scores[i])
            {
                min_score = scores[i];
                idx = i;
            }
        }
        return cycles[idx];
    }

    unordered_set<vector<int>, MyHash, MyCmp> find_cycle(const vector<vector<int>>& adj)
    {
        vector<vector<int>> d = adj;
        int min_len = N + 1;
        unordered_set<vector<int>, MyHash, MyCmp> paths;
        vector<vector<set<int>>> pos(N, vector<set<int>>(N));
        // pos[i][j] = k :  i -> k -> j
        for(int k = 0; k < N; ++k)
        {
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j)
                {
                    if(i == j) continue;
                    if(adj[j][k] <= 1 && adj[k][i] <= 1 && d[i][j] + adj[j][k] + adj[k][i] <= min_len)
                    {
                        if(d[i][j] + adj[j][k] + adj[k][i] < min_len)
                        {
                            min_len = d[i][j] + adj[j][k] + adj[k][i];
                            paths.clear();
                        }
                        vector<vector<int>> paths_ijk = get_path(i, j, pos);
                        for(vector<int> &path: paths_ijk)
                        {
                            path.push_back(j);
                            if(i != k && k != j)
                                path.push_back(k);
                            path.push_back(i);
                            paths.insert(path);
                        }
                    }
                }
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j)
                {
                    if(d[i][j] > d[i][k] + d[k][j])
                    {
                        d[i][j] = d[i][k] + d[k][j];
                        pos[i][j].clear();
                        if(i != k && k != j)
                            pos[i][j].insert(k); // i -> k -> j
                    }
                    else if(d[i][j] == d[i][k] + d[k][j])
                        if(i != k && k != j)
                            pos[i][j].insert(k);
                }
        }
        return paths;
    }

    vector<vector<int>> get_path(int i, int j, const vector<vector<set<int>>>& pos)
    {
        if(pos[i][j].empty())
            return {{}};
        // pos[i][j] = k :  i -> k -> j
        vector<vector<int>> result;
        for(int k: pos[i][j])
        {
            vector<vector<int>> result_left = get_path(i, k, pos);
            vector<vector<int>> result_right = get_path(k, j, pos);
            for(vector<int> &l: result_left)
                for(vector<int> &r: result_right)
                {
                    vector<int> path = l;
                    path.push_back(k);
                    path.insert(path.end(), r.begin(), r.end());
                    result.push_back(path);
                }
        }
        return result;
    }

    int check(const vector<vector<int>>& D)
    {
        int ans = 0;
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                ans += D[i][j];
            }
        }
        return ans;
    }
};

// 优先级队列BFS
// 超时
// 这里边权是 1，直接优先级队列肯定不好
// Astar
struct State
{
    string s;
    int d;
    int h;
    State(string& s, int d, int h):s(s),d(d),h(h){}
};

string A_global;

struct Cmp
{
    bool operator()(const State& s1, const State& s2) const
    {
        return s1.d + s1.h > s2.d + s2.h;
    }
};

class Solution_4 {
public:
    int kSimilarity(string A, string B) {
        int n = A.size();
        A_global = A;
        priority_queue<State, vector<State>, Cmp> pq;
        unordered_set<string> visited;
        pq.push(State(A, 0, h(A, B)));
        while(!pq.empty())
        {
            State s = pq.top();
            pq.pop();
            if(s.s == B)
                return s.d;
            if(visited.count(s.s) > 0)
                continue;
            visited.insert(s.s);
            int i = 0;
            while(s.s[i] == B[i])
                ++i;
            // son[i] != B[i] 的位置
            // 从 son[i+1..n-1] 找到所有 B[i] 位置进行交换
            for(int j = i + 1; j < n; ++j)
            {
                if(s.s[j] == B[i])
                {
                    swap(s.s[i], s.s[j]);
                    if(visited.count(s.s) == 0)
                    {
                        State nxt(s.s, s.d + 1, h(s.s, B));
                        pq.push(nxt);
                    }
                    swap(s.s[i], s.s[j]);
                }
            }
        }
        return -1;
    }

private:
    int h(const string &s, const string &B)
    {
        int n = s.size();
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if(s[i] != B[i])
                ++cnt;
        return (cnt + 1) / 2;
    }
};


// DFS
class Solution_5 {
private:
    void dfs(string& s, const string& t, int deep, int& min_deep)
    {
        if(deep + h(s, t) >= min_deep)
            return;
        if(s == t)
        {
            min_deep = min(min_deep, deep);
            return;
        }
        int n = t.size();
        int i = 0;
        while(i < n && s[i] == t[i])
            ++i;
        for(int j = i + 1; j < n; ++j)
        {
            if(s[j] == t[i])
            {
                swap(s[i], s[j]);
                dfs(s, t, deep + 1, min_deep);
                swap(s[i], s[j]);
            }
        }
    }

    int h(const string &s, const string &B)
    {
        int n = s.size();
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if(s[i] != B[i])
                ++cnt;
        return (cnt + 1) / 2;
    }

public:
    int kSimilarity(string A, string B) {
        int n = A.size();
        int min_deep = n;
        dfs(A, B, 0, min_deep);
        if(min_deep == n)
            return -1;
        return min_deep;
    }
};

// ID
class Solution_6 {
private:
    bool dfs(string& s, const string& t, int deep, const int max_deep)
    {
        if(deep > max_deep)
            return false;
        if(s == t)
            return true;
        int n = t.size();
        int i = 0;
        while(i < n && s[i] == t[i])
            ++i;
        for(int j = i + 1; j < n; ++j)
        {
            if(s[j] == t[i])
            {
                swap(s[i], s[j]);
                if(dfs(s, t, deep + 1, max_deep))
                    return true;
                swap(s[i], s[j]);
            }
        }
        return false;
    }

public:
    int kSimilarity(string A, string B) {
        int n = A.size();
        int depth = 0;
        while(depth < n && !dfs(A, B, 0, depth))
            ++depth;
        if(depth == n)
            return -1;
        return depth;
    }
};


// IDAstar
class Solution {
private:
    bool dfs(string& s, const string& t, int deep, const int max_deep)
    {
        if(deep + h(s, t) > max_deep)
            return false;
        if(s == t)
            return true;
        int n = t.size();
        int i = 0;
        while(i < n && s[i] == t[i])
            ++i;
        for(int j = i + 1; j < n; ++j)
        {
            if(s[j] == t[i])
            {
                swap(s[i], s[j]);
                if(dfs(s, t, deep + 1, max_deep))
                    return true;
                swap(s[i], s[j]);
            }
        }
        return false;
    }

    int h(const string &s, const string &B)
    {
        int n = s.size();
        int cnt = 0;
        for(int i = 0; i < n; ++i)
            if(s[i] != B[i])
                ++cnt;
        return (cnt + 1) / 2;
    }

public:
    int kSimilarity(string A, string B) {
        int n = A.size();
        int depth = 0;
        while(depth < n && !dfs(A, B, 0, depth))
            ++depth;
        if(depth == n)
            return -1;
        return depth;
    }


};
