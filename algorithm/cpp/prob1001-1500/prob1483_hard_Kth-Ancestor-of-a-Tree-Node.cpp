// prob1483: Kth Ancestor of a Tree Node

/*
 * You are given a tree with n nodes numbered from 0 to n-1 in the form of a parent array where parent[i] is the parent of node i. The root of the tree is node 0.
 * Implement the function getKthAncestor(int node, int k) to return the k-th ancestor of the given node. If there is no such ancestor, return -1.
 * The k-th ancestor of a tree node is the k-th node in the path from that node to the root.
 */

/*
 * Example:
 *
 *
 *
 * Input:
 * ["TreeAncestor","getKthAncestor","getKthAncestor","getKthAncestor"]
 * [[7,[-1,0,0,1,1,2,2]],[3,1],[5,2],[6,3]]
 *
 * Output:
 * [null,1,0,-1]
 *
 * Explanation:
 * TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);
 *
 * treeAncestor.getKthAncestor(3, 1);  // returns 1 which is the parent of 3
 * treeAncestor.getKthAncestor(5, 2);  // returns 0 which is the grandparent of 5
 * treeAncestor.getKthAncestor(6, 3);  // returns -1 because there is no such ancestor
 */

/*
 * Constraints:
 * 1 <= k <= n <= 5*10^4
 * parent[0] == -1 indicating that 0 is the root node.
 * 0 <= parent[i] < n for all 0 < i < n
 * 0 <= node < n
 * There will be at most 5*10^4 queries.
 */

#include <vector>
#include <algorithm>

using namespace std;

// 倍增法
class TreeAncestor_2 {
public:
    TreeAncestor_2(int n, vector<int>& parent) {
        // fa[i][j] := 从 i 爬 2 ^ j 步所到点的 id
        // fa[i][0] := 从 i 爬 1 不所到点的 id
        fa = vector<vector<int> >(n, vector<int>(M));
        for(int i = 0; i < n; ++i)
            fa[i][0] = parent[i];
        for(int j = 1; j < M; ++j)
            fa[0][j] = -1;
        for(int j = 1; j < M; ++j)
            for(int i = 0; i < n; ++i)
            {
                if(fa[i][j - 1] == -1)
                    fa[i][j] = -1;
                else
                    fa[i][j] = fa[fa[i][j - 1]][j - 1];
            }

    }

    int getKthAncestor(int node, int k) {
        for(int i = M - 1; i >= 0; --i)
        {
            if(k & (1 << i))
                node = fa[node][i];
            if(node == -1)
                break;
        }
        return node;
    }

private:
    const int M = 16;
    vector<vector<int> > fa;
};

// DFS 序
class TreeAncestor {
public:
    TreeAncestor(int n, vector<int>& parent) {
        g = vector<vector<int> >(n);
        for(int node = 1; node < n; ++node)
            g[parent[node]].push_back(node);
        id = vector<int>(n, -1);
        nodeid = vector<int>(n, -1);
        level_dfsids = vector<vector<int>>();
        node_level = vector<int>(n, -1);
        int dfsid = 0;
        dfs(0, dfsid, 0);

    }

    int getKthAncestor(int node, int k) {
        int level = node_level[node];
        int ancestor_level = level - k;
        if(ancestor_level < 0)
            return -1;
        int dfsid = id[node];
        // 大于等于 dfsid 的最小 it
        auto it = lower_bound(level_dfsids[ancestor_level].begin(), level_dfsids[ancestor_level].end(), dfsid);
        int ancestor_dfsid = *(--it);
        return nodeid[ancestor_dfsid];
    }

private:
    vector<int> id; // nodeid -> dfsid
    vector<int> nodeid; // nodeid -> dfsid
    vector<int> node_level; // nodeid -> level
    vector<vector<int>> level_dfsids; // level -> dfsids
    vector<vector<int>> g; // 邻接表

    void dfs(int node, int& dfsid, int level)
    {
        id[node] = dfsid;
        nodeid[dfsid] = node;
        if((int)level_dfsids.size() <= level)
            level_dfsids.push_back({});
        level_dfsids[level].push_back(dfsid);
        node_level[node] = level;
        for(int son: g[node])
        {
            dfsid += 1;
            dfs(son, dfsid, level + 1);
        }
    }
};
