#include <cmath>
#include <vector>
#include <queue>

using namespace std;

struct To
{
    int v, w;
    To(int v, int w):v(v),w(w){}
};

struct Cmp
{
    bool operator()(const To& e1, const To& e2) const
    {
        return e1.w > e2.w;
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> adj(n, vector<int>(n, 0));
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j)
            {
                int d = manhattan(points[i][0], points[i][1], points[j][0], points[j][1]);
                adj[i][j] = adj[j][i] = d;
            }
        vector<bool> visited(n, false);
        int cost = 0;
        priority_queue<To, vector<To>, Cmp> pq; // (w, v)
        pq.push(To(0, 0));
        while(!pq.empty())
        {
            To cur = pq.top();
            pq.pop();
            if(visited[cur.v])
                continue;
            visited[cur.v] = true;
            cost += cur.w;
            for(int son = 0; son < n; ++son)
            {
                if(visited[son]) continue;
                pq.push(To(son, adj[cur.v][son]));
            }
        }
        return cost;
    }

private:
    int manhattan(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }
};
