// prob802: Find Eventual Safe States

/*
 * n a directed graph, we start at some node and every turn, walk along a directed edge of the graph.  If we
 * reach a node that is terminal (that is, it has no outgoing directed edges), we stop.
 * Now, say our starting node is eventually safe if and only if we must eventually walk to a
 * terminal node.  More specifically, there exists a natural number K so that for any choice of where to walk,
 * we must have stopped at a terminal node in less than K steps.
 * Which nodes are eventually safe?  Return them as an array in sorted order.
 * The directed graph has N nodes with labels 0, 1, ..., N-1, where N is the length of graph.  The graph is
 * given in the following form: graph[i] is a list of labels j such that (i, j) is a directed edge of the graph.
 */

/*
 * Example:
 * Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
 * Output: [2,4,5,6]
 * Here is a diagram of the above graph.
 */

/*
 * Note:
 * graph will have length at most 10000.
 * The number of edges in the graph will not exceed 32000.
 * Each graph[i] will be a sorted list of different integers, chosen within the range [0, graph.length - 1].
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
 * 定义最终安全的点：从起始节点开始，可以沿某个路径到达终点，那么起始节点就是最终安全的点。
 *
 * 找到出度为0的顶点，这些点是安全的点
 * 逆向删除以出度为0的顶点为弧头的边，弧尾的出度减一
 * 重复上面两步，直到不存在出度为0的顶点
 */

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> rgraph(n); // 反向图
        vector<int> outdegrees(n, 0);
        for(int node = 0; node < n; ++node)
        {
            outdegrees[node] = graph[node].size();
            for(int son: graph[node])
                rgraph[son].push_back(node);
        }
        queue<int> q;
        for(int node = 0; node < n; ++node)
        {
            if(outdegrees[node] == 0)
                q.push(node);
        }
        vector<int> result;
        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            result.push_back(cur);
            for(int parent: rgraph[cur])
            {
                // son -> cur
                --outdegrees[parent];
                if(outdegrees[parent] == 0)
                    q.push(parent);
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};

// 我们同样可以使用深度优先搜索的方法判断图中的每个节点是否能走到环中。对于每个节点，
// 我们有三种染色的方法：白色表示该节点还没有被访问过；灰色表示该节点在栈中（这一轮搜索中被访问过）或者在环中；
// 黑色表示该节点的所有相连的节点都被访问过，且该节点不在环中。
// 如果搜索过程中，我们没有遇到灰色的节点，那么在回溯到当前节点时，我们把它从灰色变成黑色，即表示它是一个安全的节点。
