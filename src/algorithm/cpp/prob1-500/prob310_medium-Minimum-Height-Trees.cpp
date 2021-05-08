// prob310: Minimum Height Trees

/*
 * For an undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree.
 * Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph,
 * write a function to find all the MHTs and return a list of their root labels.
 */

/*
 * Format
 * The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).
 * You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and
 * thus will not appear together in edges.
 */

/*
 * put: n = 4, edges = [[1, 0], [1, 2], [1, 3]]
 *         0
 *         |
 *         1
 *        / \
 *       2   3
 *
 * Output: [1]
 * Example 2 :
 * Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
 *
 *      0  1  2
 *       \ | /
 *         3
 *         |
 *         4
 *         |
 *         5
 * Output: [3, 4]
 */

#include <queue>
#include <vector>
#include <climits>

using namespace std;

// BFS
// TLE
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int> > g(n); // 邻接表
        for(vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        queue<int> q;
        vector<int> level_nodes;
        vector<bool> visited(n, false);
        vector<int> result;
        int min_h = INT_MAX;
        for(int i = 0; i < n; ++i)
        {
            if(g[i].empty()) continue; // 该节点已经删掉
            // i 号点为根
            visited.assign(n, false);
            q.push(i);
            visited[i] = true;
            int level = 0;
            while(!q.empty())
            {
                ++level;
                level_nodes.clear();
                while(!q.empty())
                {
                    level_nodes.push_back(q.front());
                    q.pop();
                }
                for(int node: level_nodes)
                {
                    if((int)g[node].size() == 1)
                    {
                        g[node].clear();
                        continue;
                    }
                    for(int son: g[node])
                    {
                        if(visited[son]) continue;
                        q.push(son);
                        visited[son] = true;
                    }
                }
            }
            if(level < min_h)
            {
                min_h = level;
                result.clear();
                result.push_back(i);
            }
            else if(level == min_h)
                result.push_back(i);
        }
        return result;
    }
};

// 树形DP
class Solution_2 {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector<vector<int> > g(n); // 邻接表
        for(vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        vector<int> max_height(n, 0), t(n, 0);
        // 第一次DFS记录每个结点在作为子树根结点的最大高度。
        dfs_1(0, -1, max_height, g);
        // 第二次DFS补全每个结点作为总根结点的最大高度，差距就在于需要统计上从父结点传递过来的子树分支。
        dfs_2(0, -1, max_height, t, g);

        int min_ans = n;
        vector<int> ans;
        for(int i = 0; i < n; ++i)
        {
            if(min_ans > max_height[i])
            {
                min_ans = max_height[i];
                ans.clear();
                ans.push_back(i);
            }
            else if(min_ans == max_height[i])
                ans.push_back(i);
        }
        return ans;
    }

private:
    void dfs_1(int u, int fa, vector<int>& max_height, vector<vector<int> >& g)
    {
        max_height[u] = 0;
        for(auto &v: g[u])
        {
            if(v == fa) continue;
            dfs_1(v, u, max_height, g);
            max_height[u] = max(max_height[u], max_height[v] + 1);
        }
    }

    void dfs_2(int u, int fa, vector<int>& max_height, vector<int>& t, vector<vector<int> >& g)
    {
        max_height[u] = max(max_height[u], t[u]);
        int max_1 = 0, max_2 = 0; // 这里需要最大高度和次大高度
        for(auto &v: g[u])
        {
            if(v == fa) continue;
            if(max_1 < max_height[v] + 1)
            {
                max_2 = max_1;
                max_1 = max_height[v] + 1;
            }
            else if(max_2 < max_height[v] + 1)
                max_2 = max_height[v] + 1;
        }
        for(auto &v: g[u])
        {
            if(v == fa) continue;
            if (max_1 == max_height[v] + 1) {
                // u 在 fa 的最长链上
                t[v] = max(t[u], max_2) + 1;
                dfs_2(v, u, max_height, t, g);
            }
            else {
                t[v] = max(t[u], max_1) + 1;
                dfs_2(v, u, max_height, t, g);
            }
        }
    }
};

// 拓扑排序
class Solution_3 {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 1) return vector<int>(1, 0);
        vector<vector<int> > g(n); // 邻接表
        vector<int> indegrees(n, 0);
        for(vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
            ++indegrees[edge[0]];
            ++indegrees[edge[1]];
        }

        queue<int> q;
        for(int i = 0; i < n; ++i)
            if(indegrees[i] == 1)
                q.push(i);

        vector<int> level_nodes;
        vector<int> result;
        int i = 0;
        while(!q.empty())
        {
            if(i == n - 1 || i == n - 2)
            {
                while(!q.empty())
                {
                    result.push_back(q.front());
                    q.pop();
                }
            }
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
                ++i;
            }
            for(int node: level_nodes)
            {
                for(int son: g[node])
                {
                    --indegrees[son];
                    if(indegrees[son] == 1)
                        q.push(son);
                }
            }
        }
        return result;
    }
};
