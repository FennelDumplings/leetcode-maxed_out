// prob1584: Min Cost to Connect All Points

/*
 * https://leetcode-cn.com/problems/min-cost-to-connect-all-points/
 */

#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <set>

using namespace std;

// 堆 Prim，O(ElogE)
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

class Solution_2 {
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

// O(N^2)
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
        int cost = 0;
        vector<int> visited(n, false);
        // 选择 visited[i] && !visited[j] 的边 ij 中 adj[i][j] 最小的
        vector<int> d(n, INT_MAX / 2);
        // d[j] := !visited[j] 成立的最小的 adj[i][j]
        d[0] = 0;
        for(int cnt = 1; cnt <= n; ++cnt) // 选出 n 个点
        {
            // 选出使得 d[j] 最小的 j
            // !visited[j] 且使得 adj[i][j] 最小的 j
            int minx = INT_MAX / 2;
            int minx_j = -1;
            for(int j = 0; j < n; ++j)
            {
                if(!visited[j] && d[j] < minx)
                {
                    minx = d[j];
                    minx_j = j;
                }
            }
            cost += minx;
            visited[minx_j] = true;
            // 更新与 minx_j 关联的边
            const int &i = minx_j;
            for(int j = 0; j < n; ++j)
                if(!visited[j] && d[j] > adj[i][j])
                    d[j] = adj[i][j];
        }
        return cost;
    }

private:
    int manhattan(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }
};
