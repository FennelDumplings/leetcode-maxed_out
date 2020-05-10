// 20200210
// 3. 收集树上所有苹果的最少时间

/*
 * 给你一棵有 n 个节点的无向树，节点编号为 0 到 n-1 ，它们中有一些节点有苹果。通过树上的一条边，
 * 需要花费 1 秒钟。你从 节点 0 出发，请你返回最少需要多少秒，可以收集到所有苹果，并回到节点 0 。
 * 无向树的边由 edges 给出，其中 edges[i] = [fromi, toi] ，表示有一条边连接 from 和 toi 。除此以外，
 * 还有一个布尔数组 hasApple ，其中 hasApple[i] = true 代表节点 i 有一个苹果，否则，节点 i 没有苹果。
 */

/*
 * 示例 1：
 * 输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,true,true,false]
 * 输出：8
 * 解释：上图展示了给定的树，其中红色节点表示有苹果。一个能收集到所有苹果的最优方案由绿色箭头表示。
 * 示例 2：
 * 输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,true,false,false,true,false]
 * 输出：6
 * 解释：上图展示了给定的树，其中红色节点表示有苹果。一个能收集到所有苹果的最优方案由绿色箭头表示。
 * 示例 3：
 * 输入：n = 7, edges = [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], hasApple = [false,false,false,false,false,false,false]
 * 输出：0
 */

/*
 * 提示：
 * 1 <= n <= 10^5
 * edges.length == n-1
 * edges[i].length == 2
 * 0 <= fromi, toi <= n-1
 * fromi < toi
 * hasApple.length == n
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int> > g(n);
        for(const vector<int> &edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        int result = 0;
        vector<bool> visited(n);
        _postOrder(g, 0, result, hasApple, visited);
        return result;
    }

private:
    bool _postOrder(const vector<vector<int> >& g, int cur, int& result, const vector<bool>& hasApple, vector<bool>& visited)
    {
        // 返回值代表子树上有无苹果
        visited[cur] = true;
        bool subtree_hasapple = false;
        for(int son: g[cur])
        {
            if(visited[son]) continue;
            if(_postOrder(g, son, result, hasApple, visited))
            {
                subtree_hasapple = true;
                result += 2;
            }
        }
        if(hasApple[cur]) subtree_hasapple = true;
        return subtree_hasapple;
    }
};
