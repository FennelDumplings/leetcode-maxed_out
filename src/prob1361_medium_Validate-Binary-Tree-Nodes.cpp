// prob1361: Validate Binary Tree Nodes

/*
 * https://leetcode-cn.com/problems/validate-binary-tree-nodes/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        vector<int> indegrees(n), outdegrees(n);
        vector<vector<int>> g(n);
        for(int u = 0; u < n; ++u)
        {
            if(leftChild[u] != -1)
            {
                ++outdegrees[u];
                ++indegrees[leftChild[u]];
                g[u].push_back(leftChild[u]);
            }
            if(rightChild[u] != -1)
            {
                ++outdegrees[u];
                ++indegrees[rightChild[u]];
                g[u].push_back(rightChild[u]);
            }
        }
        int s = -1;
        for(int i = 0; i < n; ++i)
        {
            if(indegrees[i] == 0)
            {
                if(s != -1)
                    return false;
                s = i;
            }
            if(indegrees[i] > 1)
                return false;
        }
        if(s == -1)
            return false;
        for(int i: outdegrees)
            if(i > 2)
                return false;
        return connect(g, s);
    }

private:
    bool connect(const vector<vector<int>>& g, int s)
    {
        int n = g.size();
        vector<bool> visited(n, false);
        visited[s] = true;
        dfs(g, s, visited);
        for(bool flag: visited)
            if(!flag)
                return false;
        return true;
    }

    void dfs(const vector<vector<int>>& g, int u, vector<bool>& visited)
    {
        for(int v: g[u])
        {
            if(visited[v])
                continue;
            visited[v] = true;
            dfs(g, v, visited);
        }
    }
};
