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

// 拓扑排序
class Solution_2 {
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

void dfs1(const vector<vector<int>>& g, int node, vector<int>& backtrack_seq, vector<bool>& visited, vector<vector<int>>& gt)
{
    for(int son: g[node])
    {
        gt[son].push_back(node);
        if(visited[son])
            continue;
        visited[son] = true;
        dfs1(g, son, backtrack_seq, visited, gt);
    }
    backtrack_seq.push_back(node);
}

void dfs2(const vector<vector<int>>& gt, int node, vector<bool>& visited, vector<vector<int>>& scc)
{
    for(int son: gt[node])
    {
        if(visited[son]) continue;
        scc.back().push_back(son);
        visited[son] = true;
        dfs2(gt, son, visited, scc);
    }
}

vector<vector<int>> get_scc(const vector<vector<int>>& g)
{
    int N = g.size();
    vector<bool> visited(N, false); // 标记 dfs1 已访问
    vector<int> backtrack_seq; // 按回溯顺序插入
    vector<vector<int>> gt(N); // 反图
    for(int i = 0; i < N; ++i)
    {
        if(visited[i]) continue;
        visited[i] = true;
        dfs1(g, i, backtrack_seq, visited, gt);
    }
    visited.assign(N + 1, false); // 标记 dfs2 已访问
    vector<vector<int>> scc;
    for(auto it = backtrack_seq.rbegin(); it != backtrack_seq.rend(); ++it)
    {
        int node = *it;
        if(visited[node]) continue;
        scc.push_back({});
        scc.back().push_back(node);
        visited[node] = true;
        dfs2(gt, node, visited, scc);
    }
    return scc;
}

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int N = graph.size();
        vector<vector<int>> scc = get_scc(graph);
        vector<int> c(N, -1);
        int m = scc.size();
        vector<vector<int>> sg(m); // shrink graph，缩点后的图
        for(int i = 0; i < m; ++i)
        {
            for(int node: scc[i])
                c[node] = i;
        }
        for(int i: c) cout << i << " ";
        cout << endl;
        vector<bool> self_cycle(N, false);
        for(int node = 0; node < N; ++node)
            for(int son: graph[node])
            {
                if(node == son)
                    self_cycle[node] = true;
                if(c[node] != c[son])
                    sg[c[node]].push_back(c[son]);
            }
        vector<int> safe(m, 0);
        for(int i = 0; i < m; ++i)
            if((int)scc[i].size() == 1 && !self_cycle[scc[i][0]])
                safe[i] = 1;
        for(int i: safe) cout << i << " ";
        cout << endl;
        for(int i = 0; i < m; ++i)
        {
            if(safe[i] != 1) continue;
            safe[i] = 2;
            dfs(sg, i, safe);
        }
        vector<int> result;
        for(int i = 0; i < N; ++i)
        {
            if(safe[c[i]] == 2)
                result.push_back(i);
        }
        return result;
    }

private:
    bool dfs(const vector<vector<int>>& g, int node, vector<int>& safe)
    {
        for(int son: g[node])
        {
            if(safe[son] == 1)
            {
                safe[son] = 2;
                dfs(g, son, safe);
            }
            if(safe[son] == 0)
            {
                safe[node] = 0;
                return false;
            }
        }
        return true;
    }
};
