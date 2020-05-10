// prob834: Sum of Distances in Tree

/*
 * An undirected, connected tree with N nodes labelled 0...N-1 and N-1 edges are given.
 * The ith edge connects nodes edges[i][0] and edges[i][1] together.
 * Return a list ans, where ans[i] is the sum of the distances between node i and all other nodes.
 */

/*
 * Example 1:
 * Input: N = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
 * Output: [8,12,6,10,10,10]
 * Explanation:
 * Here is a diagram of the given tree:
 *   0
 *  / \
 * 1   2
 *    /|\
 *   3 4 5
 * We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
 * equals 1 + 1 + 2 + 2 + 2 = 8.  Hence, answer[0] = 8, and so on.
 */

/*
 * Note: 1 <= N <= 10000
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        vector<vector<int> > g(N);
        for(const vector<int>& edge: edges)
        {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(N, false);
        vector<int> father(N, -1);
        vector<int> result(N);
        vector<int> cnts(N);
        _postOrder(g, 0, visited, father, result, cnts);
        visited.assign(N, false);
        _preOrder(g, 0, visited, father, result, cnts);
        return result;
    }

private:
    // 每个节点的答案分 left, right ,father 三部分
    // _postOrder 负责 left 和 right 两部分
    void _postOrder(const vector<vector<int> >& g, int cur, vector<bool>& visited,
            vector<int>& father, vector<int>& result, vector<int>& cnts)
    {
        // 返回值：子树的节点个数
        // len: 子树的根 root 到树中所有节点的距离值和
        // cnt: 子树的节点个数
        visited[cur] = true;
        int cnt = 0;
        int len = 0;
        for(int son: g[cur])
        {
            if(visited[son]) continue;
            father[son] = cur;
            _postOrder(g, son, visited, father, result, cnts);
            cnt += cnts[son];
            len += cnts[son] + result[son];
        }
        cnts[cur] = cnt + 1;
        result[cur] = len;
    }

    // _preOrder 负责 father 的部分
    void _preOrder(const vector<vector<int> >& g, int cur, vector<bool>& visited,
            const vector<int>& father, vector<int>& result, const vector<int>& cnts)
    {
        // father_len := 父节点的三部分总和
        visited[cur] = true;
        if(father[cur] != -1)
            result[cur] += (result[father[cur]] - cnts[cur] - result[cur]) + (cnts[0] - cnts[cur]);
        for(int son: g[cur])
        {
            if(visited[son]) continue;
            _preOrder(g, son, visited, father, result, cnts);
        }
    }
};
