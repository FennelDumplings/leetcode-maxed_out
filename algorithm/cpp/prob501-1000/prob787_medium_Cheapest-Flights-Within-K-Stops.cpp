// prob787:

/*
 * There are n cities connected by m flights. Each flight starts from city u and arrives at v with a price w.
 * Now given all the cities and flights, together with starting city src and the destination dst, your task is to
 * find the cheapest price from src to dst with up to k stops. If there is no such route, output -1.
 */

/*
 * Note:
 * The number of nodes n will be in range [1, 100], with nodes labeled from 0 to n - 1.
 * The size of flights will be in range [0, n * (n - 1) / 2].
 * The format of each flight will be (src, dst, price).
 * The price of each flight will be in the range [1, 10000].
 * k is in the range of [0, n - 1].
 * There will not be any duplicated flights or self cycles.
 */

/*
 * Example 1:
 * Input:
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 1
 * Output: 200
 * Explanation:
 * The graph looks like this:
 * The cheapest price from city 0 to city 2 with at most 1 stop costs 200, as marked red in the picture.
 * Example 2:
 * Input:
 * n = 3, edges = [[0,1,100],[1,2,100],[0,2,500]]
 * src = 0, dst = 2, k = 0
 * Output: 500
 * Explanation:
 * The graph looks like this:
 * The cheapest price from city 0 to city 2 with at most 0 stop costs 500, as marked blue in the picture.
 */

#include <vector>
#include <climits>

using namespace std;

// bellman ford
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        vector<vector<vector<int> > > g(n);
        for(vector<int> &flight: flights)
            g[flight[0]].push_back({flight[1], flight[2]});

        vector<vector<int> > d = bellman_ford(g, src, n, K + 1);

        int result = INT_MAX;
        for(int i = 1; i <= K + 1; ++i)
            if(d[i][dst] != -1)
                result = min(result, d[i][dst]);
        return result == INT_MAX ? -1 : result;
    }

private:
    vector<vector<int> > bellman_ford(vector<vector<vector<int> > >& g, int start, int N, int K)
    {
        vector<vector<int> > d(K + 1, vector<int>(N, -1));
        d[0][start] = 0;

        for(int cnt = 1; cnt <= K; ++cnt)
            for(int u = 0; u <= N - 1; ++u)
            {
                if(d[cnt - 1][u] == -1) continue;
                for(vector<int> &son: g[u])
                {
                    int v = son[0], w = son[1];
                    if(d[cnt - 1][u] + w < d[cnt][v] || d[cnt][v] == -1)
                        d[cnt][v] = d[cnt - 1][u] + w;
                }
            }

        return d;
    }
};
