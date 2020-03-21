// prob1245: Tree Diameter

/*
 *
 * Given an undirected tree, return its diameter: the number of edges in a longest path in that tree.
 * The tree is given as an array of edges where edges[i] = [u, v] is a bidirectional edge between nodes u and v.  Each node has labels in the set {0, 1, ..., edges.length}.
 */

/*
 * Constraints:
 * 0 <= edges.length < 10^4
 * edges[i][0] != edges[i][1]
 * 0 <= edges[i][j] <= edges.length
 * The given edges form an undirected tree.
 */

/*
 * Example 1:
 * Input: edges = [[0,1],[0,2]]
 * Output: 2
 * Explanation:
 * A longest path of the tree is the path 1 - 0 - 2.
 * Example 2:
 * Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
 * Output: 4
 * Explanation:
 * A longest path of the tree is the path 3 - 2 - 1 - 4 - 5.
 */

#include <vector>

using namespace std;

// 邻接表的树形DP
class Solution {
public:
    int treeDiameter(vector<vector<int>>& edges) {
        int n = edges.size();
        vector<vector<int> > g(n + 1);
        for(const auto &e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        int ans = 0;
        dfs(0, -1, g, ans);
        return ans;
    }

private:
    int dfs(int x, int fa, const vector<vector<int> >& g, int& ans)
    {
        int max1 = 0, max2 = 0;
        for(int v: g[x])
        {
            if(v != fa)
            {
                int t = dfs(v, x, g, ans) + 1;
                if(max1 < t)
                {
                    max2 = max1;
                    max1 = t;
                }
                else if(max2 < t)
                    max2 = t;
            }
        }
        ans = max(ans, (max1 + max2));
        return max1;
    }
};
