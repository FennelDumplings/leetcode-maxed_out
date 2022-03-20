#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int networkBecomesIdle(vector<vector<int>>& edges, vector<int>& patience) {
        // 从 0 号开始 BFS，得到每个点到 0 的最短距离, dist[i]
        // i 号点从发出到接收回信的时间为 dist[i] * 2
        // 如果 dist[i] * 2 <= patience[i]，则 idle[i] = dist[i] * 2
        // 否则，dist[i] * 2 时接收到回信，此时有重发的消息还在路上，已经走了 dist[i] * 2 % patience[i]
        //      还剩下 dist[i] * 2 - ((dist[i] * 2) % patience[i]
        int n = patience.size();
        vector<vector<int>> g(n);
        for(const vector<int>& e: edges)
        {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }

        vector<int> dist(n, 0);
        queue<int> q;
        q.push(0);
        int d = 0;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v: g[u])
            {
                if(dist[v] != 0)
                    continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }

        vector<int> idle(n, 0);
        for(int i = 1; i < n; ++i)
            dist[i] *= 2;
        for(int i = 1; i < n; ++i)
        {
            idle[i] = dist[i];
            if(dist[i] > patience[i])
            {
                int r = dist[i] % patience[i];
                if(r == 0)
                    r = patience[i];
                idle[i] += dist[i] - r;
            }
        }

        int ans = 0;
        for(int i = 1; i < n; ++i)
            ans = max(ans, idle[i]);

        return ans + 1;
    }
};
