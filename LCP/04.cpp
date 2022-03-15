#include <unordered_set>
#include <vector>

/*
class Solution {
public:
    int domino(int n, int m, vector<vector<int>>& broken) {
        int n_broken = broken.size();
        vector<vector<int>> g(n * m);
        unordered_set<int> setting;
        for(const vector<int>& b: broken)
            setting.insert(key(b[0], b[1], m));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int u = key(i, j, m);
                if(setting.count(u) > 0)
                    continue;
                for(int d = 0; d < 4; ++d)
                {
                    int x = i + dx[d];
                    int y = j + dy[d];
                    if(x < 0 || x >= n || y < 0 || y >= m)
                        continue;
                    int v = key(x, y, m);
                    if(setting.count(v) > 0)
                        continue;
                    g[u].push_back(v);
                }
            }
        int ans = 0;
        vector<bool> visited;
        vector<int> match(n * m, -1);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int u = key(i, j, m);
                if(setting.count(u) > 0)
                    continue;
                visited.assign(n * m, false);
                visited[u] = true;
                if(dfs(u, g, visited, match))
                    ++ans;
            }
        return ans / 2;
    }

    bool dfs(int u, const vector<vector<int>>& g, vector<bool>& visited, vector<int>& match)
    {
        for(int v: g[u])
        {
            if(visited[v])
                continue;
            visited[v] = true;
            if(match[v] == -1 || dfs(match[v], g, visited, match))
            {
                match[v] = u;
                return true;
            }
        }
        return false;
    }

    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};

    int key(int x, int y, int m)
    {
        return x * m + y;
    }
};
*/

class Solution {
public:
    int domino(int n, int m, vector<vector<int>>& broken) {
        int n_broken = broken.size();
        setting = unordered_set<int>();
        for(const vector<int>& b: broken)
            setting.insert(key(b[0], b[1], m));
        vector<vector<int>> dp(n + 1, vector<int>(1 << m));
        dp[0][0] = 1;
        for(int i = 1; i <= n; ++i)
        {
            for(int s = 0; s < (1 << m); ++s)
            {
                if(!check1(s, i - 1, m))
                    continue;
                for(int t = 0; t < (1 << m); ++t)
                {
                    if(!check1(t, i - 1, m))
                        continue;
                    if((s & t) != 0)
                        continue;
                    if(!check2(s | t, i - 1, m))
                        continue;
                    dp[i][s] += dp[i - 1][t];
                }
            }
        }
        return dp[n][0];
    }

    unordered_set<int> setting;

    bool check2(const int s, const int i, const int m)
    {
        // 检查 s 中所有连续 0 的长度是否均为偶数(障碍点跳过)
        int j = m - 1;
        while(j >= 0)
        {
            int len = 0;
            while(j >= 0 && setting.count(key(i, j, m)) == 0 && (s >> j & 1) == 0)
            {
                --j;
                ++len;
            }
            if(len & 1)
                return false;
            while(j >= 0 && (setting.count(key(i, j, m)) > 0 || (s >> j & 1) == 1))
                --j;
        }
        return true;
    }

    bool check1(const int s, const int i, const int m)
    {
        // 检查 s 为 1 的位置是否是障碍点
        for(int j = 0; j < m; ++j)
        {
            if((s >> j & 1) == 0)
                continue;
            if(setting.count(key(i, j, m)) > 0)
                return false;
        }
        return true;
    }

    int key(int x, int y, int m)
    {
        return x * m + y;
    }
};
