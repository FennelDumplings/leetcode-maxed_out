
#include <vector>
#include <string>
#include <queue>

using namespace std;


class DAGChecker_dfs
{
    bool dfs(const vector<vector<int> >& g, int node, vector<int>& visited)
    {
        if(visited[node] == 2)
            return true;
        if(visited[node] == 1) // 环
            return false;
        visited[node] = 1;
        for(int son: g[node])
            if(!dfs(g, son, visited))
                return false;
        visited[node] = 2;
        return true;
    }

public:
    bool operator()(const vector<vector<int>>& g)
    {
        int n = g.size();
        vector<int> visited(n, 0);
        for(int i = 0; i < n; ++i)
        {
            if(visited[i] != 0) continue;
            if(!dfs(g, i, visited))
                return false;
        }
        return true;
    }
};


class DAGChecker_bfs
{
public:
    bool operator()(const vector<vector<int>>& g, vector<int> indegrees)
    {
        int n = g.size();
        queue<int> q;
        for(int i = 0; i < n; ++i)
            if(indegrees[i] == 0)
                q.push(i);

        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            --n;
            for(int son: g[cur])
            {
                --indegrees[son];
                if(indegrees[son] == 0)
                    q.push(son);
            }
        }
        return n == 0;
    }
};

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> g(n);
        vector<int> indegrees(n, 0);
        for(vector<int> &e: edges)
        {
            ++indegrees[e[1]];
            g[e[0]].push_back(e[1]);
        }
        DAGChecker_bfs dag_checker;
        if(!dag_checker(g, indegrees))
            return -1;
        // DAG
        int ans = 1;
        // dp[u][s] := 以 u 开头，颜色 s 的最大颜色值是多少
        dp = vector<vector<int>>(n, vector<int>(26, -1));
        for(int u = 0; u < n; ++u)
        {
            if(indegrees[u] > 0)
                continue;
            dfs(g, colors, u); // 以 i 为起点的最大颜色值
            for(int s = 0; s < 26; ++s)
            {
                ans = max(ans, dp[u][s]);
            }
        }
        return ans;
    }

private:
    vector<vector<int>> dp;

    void dfs(const vector<vector<int>>& g, const string& colors, int node)
    {
        if(dp[node][0] != -1)
            return;
        // node 开头的链还没算过
        for(int s = 0; s < 26; ++s)
            dp[node][s] = 0;
        for(int son: g[node])
        {
            dfs(g, colors, son);
            for(int s = 0; s < 26; ++s)
                dp[node][s] = max(dp[node][s], dp[son][s]);
        }
        ++dp[node][colors[node] - 'a'];
    }
};

