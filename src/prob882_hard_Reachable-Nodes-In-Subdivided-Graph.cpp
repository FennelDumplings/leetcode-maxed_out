// prob882: Reachable Nodes In Subdivided Graph

/*
 * Starting with an undirected graph (the "original graph") with nodes from 0 to N-1, subdivisions are made to some of the edges.
 * The graph is given as follows: edges[k] is a list of integer pairs (i, j, n) such that (i, j) is an edge of the original graph,
 * and n is the total number of new nodes on that edge. 
 * Then, the edge (i, j) is deleted from the original graph, n new nodes (x_1, x_2, ..., x_n) are added to the original graph,
 * and n+1 new edges (i, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n-1}, x_n), (x_n, j) are added to the original graph.
 * Now, you start at node 0 from the original graph, and in each move, you travel along one edge. 
 * Return how many nodes you can reach in at most M moves.
 */

/*
 * Example 1:
 * Input: edges = [[0,1,10],[0,2,1],[1,2,2]], M = 6, N = 3
 * Output: 13
 * Explanation:
 * The nodes that are reachable in the final graph after M = 6 moves are indicated below.
 * Example 2:
 * Input: edges = [[0,1,4],[1,2,6],[0,2,8],[1,3,1]], M = 10, N = 4
 * Output: 23
 */

/*
 * Note:
 * 0 <= edges.length <= 10000
 * 0 <= edges[i][0] < edges[i][1] < N
 * There does not exist any i != j for which edges[i][0] == edges[j][0] and edges[i][1] == edges[j][1].
 * The original graph has no parallel edges.
 * 0 <= edges[i][2] <= 10000
 * 0 <= M <= 10^9
 * 1 <= N <= 3000
 * A reachable node is a node that can be travelled to using at most M moves starting from node 0.
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;

using PII = pair<int, int>;

struct Point
{
    int id;
    int shortest_path; // 到 0 的最短距离
    vector<PII> edges; // 连接 id 的边 <目标点，距离>
    Point()
    {
        shortest_path = INT_MAX;
        edges = vector<PII>();
        id = -1;
    }
};

struct Cmp
{
    bool operator()(const Point& p1, const Point& p2)
    {
        return p1.shortest_path > p2.shortest_path;
    }
};

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        vector<Point> g(N);
        for(int i = 0; i < N; ++i)
            g[i].id = i;
        for(const vector<int>& ijk: edges)
        {
            int i = ijk[0], j = ijk[1], k = ijk[2];
            g[i].edges.push_back(PII(j, k + 1));
            g[j].edges.push_back(PII(i, k + 1));
        }

        vector<bool> visited(N, false);
        visited[0] = true;
        g[0].shortest_path = 0;
        priority_queue<Point, vector<Point>, Cmp> q;
        q.push(g[0]);
        int result = 1;
        while(!q.empty())
        {
            Point cur = q.top();
            q.pop();
            if(visited[cur.id]) continue;
            visited[cur.id] = true;
            for(PII edge: cur.edges)
            {
                int son = edge.first, len = edge.second;
                if(cur.shortest_path + len <= M)
                    result += len;
                else
                    result += M - cur.shortest_path;
                g[son].shortest_path = cur.shortest_path + len;
                if(g[son].shortest_path > M)
                    continue;
                q.push(g[son]);
            }
        }
        return result;
    }
};
