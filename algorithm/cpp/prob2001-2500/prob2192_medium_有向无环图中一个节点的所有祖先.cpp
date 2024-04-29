class Solution {
public:
    vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges) {
        vector<vector<int>> rg(n);
        vector<int> indegrees(n);
        for(const vector<int> &e: edges)
        {
            int u = e[0];
            int v = e[1];
            rg[v].push_back(u);
            indegrees[u] += 1;
        }

        vector<unordered_set<int>> _result(n);

        for(int u = 0; u < n; ++u)
        {
            if(indegrees[u] > 0)
                continue;
            dfs(u, rg, _result);
        }

        vector<vector<int>> result(n);

        for(int i = 0; i < n; ++i)
        {
            result[i] = vector<int>(_result[i].begin(), _result[i].end());
            sort(result[i].begin(), result[i].end());
        }

        return result;
    }

    void dfs(int u, const vector<vector<int>>& rg, vector<unordered_set<int>>& _result)
    {
        if(!_result[u].empty())
            return;
        for(int v: rg[u])
        {
            _result[u].insert(v);
            dfs(v, rg, _result);
            for(int i: _result[v])
                _result[u].insert(i);
        }
    }
};
