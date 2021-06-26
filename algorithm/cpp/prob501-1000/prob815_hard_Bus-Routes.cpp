// prob815: Bus Routes

/*
 * We have a list of bus routes. Each routes[i] is a bus route that the i-th bus repeats forever. For example if routes[0] = [1, 5, 7], this means that the first bus (0-th indexed) travels in the sequence 1->5->7->1->5->7->1->... forever.
 * We start at bus stop S (initially not on a bus), and we want to go to bus stop T. Travelling by buses only, what is the least number of buses we must take to reach our destination? Return -1 if it is not possible.
 */

/*
 * Example:
 * Input:
 * routes = [[1, 2, 7], [3, 6, 7]]
 * S = 1
 * T = 6
 * Output: 2
 * Explanation:
 * The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
 */

/*
 * Constraints:
 * 1 <= routes.length <= 500.
 * 1 <= routes[i].length <= 10^5.
 * 0 <= routes[i][j] < 10 ^ 6.
 */

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        int n_route = routes.size();
        vector<vector<int> > g(n_route, vector<int>()); // 以站点 id 建图
        // routes 中每个线路
        vector<int> starts;
        unordered_set<int> ends;
        for(int i = 0; i < n_route; ++i)
        {
            sort(routes[i].begin(), routes[i].end());
            if(find(routes[i].begin(), routes[i].end(), S) != routes[i].end())
                starts.push_back(i);
            if(find(routes[i].begin(), routes[i].end(), T) != routes[i].end())
                ends.insert(i);
        }
        vector<int> intersect(500);
        for(int i = 0; i < n_route - 1; ++i)
            for(int j = i + 1; j < n_route; ++j)
            {
                auto it = set_intersection(routes[i].begin(), routes[i].end(), routes[j].begin(), routes[j].end(), intersect.begin());
                if(it != intersect.begin())
                {
                    g[i].push_back(j);
                    g[j].push_back(i);
                }
            }
        queue<int> q;
        vector<bool> visited(n_route, false);
        for(int i: starts)
        {
            q.push(i);
            visited[i] = true;
        }
        int result = 1;
        vector<int> level_nodes;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                int cur = q.front();
                q.pop();
                if(ends.find(cur) != ends.end())
                    return result;
                level_nodes.push_back(cur);
            }
            ++result;
            for(int node: level_nodes)
            {
                for(int son: g[node])
                {
                    if(visited[son]) continue;
                    visited[son] = true;
                    q.push(son);
                }
            }
        }
        return -1;
    }
};
