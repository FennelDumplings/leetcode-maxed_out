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
        mask = (1 << m) - 1;
        vector<int> b(n + 1, 0);
        b[n] = mask;
        for(const vector<int>& broken_point: broken)
        {
            int i = broken_point[0];
            int j = broken_point[1];
            b[i] |= (1 << j);
        }
        vector<vector<int>> dp(n + 1, vector<int>(1 << m, -1));
        for(int s = 0; s < (1 << m); ++s)
            dp[n][s] = 0;
        return solve(0, (~b[0]) & mask, b, dp);
    }

    int mask;

    int solve(int i, int s, const vector<int>& b, vector<vector<int>>& dp)
    {
        if(dp[i][s] != -1)
            return dp[i][s];
        dp[i][s] = 0;
        for(int t = s; ; t = (t - 1) & s)
        {
            if((t & b[i + 1]) != 0)
                continue;
            int n1 = check1(t); // 竖着放的个数
            int n2 = check2(s & (~t)); // 横着放的个数
            dp[i][s] = max(dp[i][s], n1 + n2 + solve(i + 1, (~(t | b[i + 1])) & mask, b, dp));
            if(t == 0)
                break;
        }
        return dp[i][s];
    }

    int check2(int x)
    {
        // x 中长度为 2 的连续 1 的个数
        int n = 0;
        while(x > 0)
        {
            while(x > 0 && (x & 1) == 0)
                x >>= 1;
            x >>= 1;
            if((x & 1) == 1)
            {
                x >>= 1;
                ++n;
            }
        }
        return n;
    }

    int check1(int x)
    {
        // x 中 1 的个数
        int n = 0;
        while(x > 0)
        {
            if((x & 1) == 1)
                ++n;
            x >>= 1;
        }
        return n;
    }
};
