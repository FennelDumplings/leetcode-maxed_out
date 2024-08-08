int bfs(const vector<vector<int>>& g, int s)
{
    int n = g.size();
    vector<int> level(n, -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;
    int k = 0;
    int ans = INT_MAX / 2;
    vector<int> level_nodes;
    while(!q.empty())
    {
        level_nodes.clear();
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v: g[u])
            {
                if(level[v] == -1)
                {
                    level_nodes.push_back(v);
                    level[v] = k + 1;
                }
                else if(level[v] == k + 1)
                {
                    ans = min(ans, 2 * k + 2);
                }
                else if(level[v] == k)
                {
                    ans = min(ans, 2 * k + 1);
                }
            }
        }
        if(ans != INT_MAX / 2)
            return ans;
        for(int u: level_nodes)
            q.push(u);
        k++;
    }
    return ans;
}

class Solution {
public:
    int findShortestCycle(int n, vector<vector<int>>& edges) {
        vector<vector<int>> g(n, vector<int>());
        for(vector<int>& e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int ans = INT_MAX / 2;
        for(int s = 0; s < n; ++s)
        {
            ans = min(ans, bfs(g, s));
        }
        if(ans == INT_MAX / 2)
            return -1;
        return ans;
    }
};
