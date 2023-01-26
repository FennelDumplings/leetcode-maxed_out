// prob1257: Smallest Common Region

/*
 * https://leetcode-cn.com/problems/smallest-common-region/
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string findSmallestRegion(vector<vector<string>>& regions, string region1, string region2) {
        id = 0;
        node_id = unordered_map<string, int>();
        g = vector<vector<int>>();
        name = vector<string>();
        for(const vector<string>& l: regions)
        {
            if(l.empty()) continue;
            if(node_id.count(l[0]) == 0)
            {
                name.push_back(l[0]);
                node_id[l[0]] = id++;
                g.push_back({});
            }
            int u = node_id[l[0]];
            int n = l.size();
            for(int i = 1; i < n; ++i)
            {
                if(node_id.count(l[i]) == 0)
                {
                    name.push_back(l[i]);
                    node_id[l[i]] = id++;
                    g.push_back({});
                }
                int v = node_id[l[i]];
                g[v].push_back(u);
            }
        }
        if(node_id.count(region1) == 0 || node_id.count(region2) == 0)
            return "-1";

        int N = g.size();
        g.push_back({});
        root = N;
        for(int u = 0; u < N - 1; ++u)
        {
            if(g[u].size() == 0)
                g[u].push_back(root);
        }

        int x = node_id[region1];
        int y = node_id[region2];
        return name[lca(x, y)];
    }

private:
    unordered_map<string, int> node_id;
    vector<string> name;
    int id;
    vector<vector<int>> g; // 反图
    int root; // 超级汇

    int lca(int x, int y)
    {
        unordered_set<int> path;
        dfs1(x, root, path);
        int lca = dfs2(y, path);
        return lca;
    }

    bool dfs1(int u, const int t, unordered_set<int>& path)
    {
        path.insert(u);
        if(u == t)
            return true;
        for(int v: g[u])
        {
            if(dfs1(v, t, path))
                return true;
        }
        path.erase(u);
        return false;
    }

    int dfs2(int u, const unordered_set<int>& path)
    {
        if(path.count(u) > 0)
            return u;
        for(int v: g[u])
        {
            int res = dfs2(v, path);
            if(res != -1)
                return res;
        }
        return -1;
    }
};
