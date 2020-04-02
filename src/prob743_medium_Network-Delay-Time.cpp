// prob743: Network Delay Time

/*
 * There are N network nodes, labelled 1 to N.
 * Given times, a list of travel times as directed edges times[i] = (u, v, w), where u is the source node, v is the target node,
 * and w is the time it takes for a signal to travel from source to target.
 * Now, we send a signal from a certain node K. How long will it take for all nodes to receive the signal? If it is impossible, return -1.
 */

/*
 * Note:
 * N will be in the range [1, 100].
 * K will be in the range [1, N].
 * The length of times will be in the range [1, 6000].
 * All edges times[i] = (u, v, w) will have 1 <= u, v <= N and 0 <= w <= 100.
 */

/*
 * Example 1:
 * Input: times = [[2,1,1],[2,3,1],[3,4,1]], N = 4, K = 2
 * Output: 2
 */

#include <vector>
#include <queue>
#include <climits>

using namespace std;


// dijkstra 模板
// 跑得很慢
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<vector<int> > > g(N + 1);
        for(vector<int> edge: times)
            g[edge[0]].push_back({edge[1], edge[2]});
        vector<bool> visited(N + 1, false);
        priority_queue<vector<int>, vector<vector<int> >, Cmp> pq;
        pq.push({K, 0});
        int result = 0;
        while(!pq.empty())
        {
            vector<int> cur = pq.top();
            pq.pop();
            if(visited[cur[0]]) continue;
            visited[cur[0]] = true;
            // 已经被访问过就不能更新结果
            result = max(result, cur[1]);
            for(vector<int> son: g[cur[0]])
            {
                if(visited[son[0]]) continue;
                pq.push({son[0], son[1] + cur[1]});
            }
        }
        for(int i = 1; i <= N; ++i)
            if(!visited[i])
                return -1;
        return result;
    }

private:
    struct Cmp
    {
        bool operator() (const vector<int>& item1, const vector<int>& item2)
        {
            return item1[1] > item2[1];
        }
    };
};

// dijkstra
// 维护所有点到单源的距离，去掉 visited, 增加降距
// 比 1 快不少但还是 350 ms, 10%
class Solution_2 {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<vector<int> > > g(N + 1);
        vector<int> d(N + 1, INT_MAX / 2);
        d[K] = 0;
        for(vector<int> edge: times)
            g[edge[0]].push_back({edge[1], edge[2]});
        priority_queue<vector<int>, vector<vector<int> >, Cmp> pq;
        pq.push({K, 0});
        while(!pq.empty())
        {
            vector<int> cur = pq.top();
            pq.pop();
            if(d[cur[0]] < cur[1]) continue;
            for(vector<int> son: g[cur[0]])
            {
                if(d[son[0]] <= d[cur[0]] + son[1]) continue;
                d[son[0]] = d[cur[0]] + son[1]; // 降距
                pq.push({son[0], d[son[0]]});
            }
        }
        int result = 0;
        for(int i = 1; i <= N; ++i)
            result = max(result, d[i]);
        return result == INT_MAX / 2 ? -1 : result;
    }

private:
    struct Cmp
    {
        bool operator() (const vector<int>& item1, const vector<int>& item2)
        {
            return item1[1] > item2[1];
        }
    };
};
