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

struct Point
{
    int id;
    int shortest_path; // 到 0 的最短距离
    Point(int id = -1, int shortest_path = 0):id(id),shortest_path(shortest_path){}
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
        vector<vector<PII> > g(N);
        for(const vector<int>& ijk: edges)
        {
            int i = ijk[0], j = ijk[1], k = ijk[2];
            g[i].push_back(PII(j, k + 1));
            g[j].push_back(PII(i, k + 1));
        }

        vector<int> d = dijkstra(g, 0);
        for(int p: d)
            cout << p << endl;

        int result = 0;
        for(int i: d)
            if(i <= M)
                ++result;
        for(const vector<int>& edge: edges)
        {
            if(d[edge[0]] > M && d[edge[1]] > M)
                continue;
            else if(d[edge[0]] <= M && d[edge[1]] <= M)
                result += min(edge[2], 2 * M - d[edge[0]] - d[edge[1]]);
            else if(d[edge[0]] <= M)
                result += min(edge[2], M - d[edge[0]]);
            else
                result += min(edge[2], M - d[edge[1]]);
        }
        return result;
    }

private:
    using PII = pair<int, int>;
    vector<int> dijkstra(const vector<vector<PII> >& g, int start)
    {
        int N = g.size();
        vector<bool> visited(N, false);
        vector<int> d(N, INT_MAX);
        priority_queue<Point, vector<Point>, Cmp> q;
        q.push(Point(start, 0));
        while(!q.empty())
        {
            Point cur = q.top();
            q.pop();
            if(visited[cur.id]) continue;
            visited[cur.id] = true;
            d[cur.id] = cur.shortest_path;
            for(PII edge: g[cur.id])
            {
                int son_id = edge.first, len = edge.second;
                q.push(Point(son_id, cur.shortest_path + len));
            }
        }
        return d;
    }
};
