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
#include <list>

using namespace std;


// dijkstra 模板 堆实现
// 跑得很慢 700ms 5%
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<vector<int> > > g(N + 1);
        for(vector<int> &edge: times)
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

// dijkstra 堆实现
// 维护所有点到单源的距离，去掉 visited, 增加降距
// 比 1 快不少但还是 240 ms, 20%
class Solution_2 {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<vector<int> > > g(N + 1);
        vector<int> d(N + 1, INT_MAX / 2);
        d[K] = 0;
        for(vector<int> &edge: times)
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

// https://leetcode-cn.com/problems/network-delay-time/solution/c-bellman-forddijkstrafloydspfa-by-gez1994/

// dijkstra 数组实现
// 邻接矩阵 240ms
class Solution_4 {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<int> > g(N + 1, vector<int>(N + 1, -1)); // 邻接矩阵
        for(int i = 0; i < (int)times.size(); i++)
            g[times[i][0]][times[i][1]] = times[i][2];
        vector<int> d(N + 1, -1);
        for(int i = 1; i <= N; i++)
            d[i] = g[K][i];
        d[K] = 0;
        vector<bool> visited(N + 1, false);
        visited[K] = true;

        // 遍历除K本身节点之外的所有N-1个节点
        for(int c = 0; c < N; c++)
        {
            int min_val = INT_MAX / 2, min_idx = 1;
            // 遍历所有节点，找到离K最近的节点
            for(int i = 1; i <= N; i++)
                if(d[i] != -1 && !visited[i] && d[i] < min_val)
                {
                    min_idx = i;
                    min_val = d[i];
                }
            visited[min_idx] = true;
            // 根据刚刚找到的最短距离节点，通过该节点更新K节点与其他的节点的距离
            for(int i = 1; i <= N; i++)
                // 如果已更新的最短节点可以到达当前节点
                if(g[min_idx][i] != -1)
                {
                    // 如果已更新的最短节点可以到达当前节点
                    if(d[i] != -1)
                        d[i] = min(d[i], min_val + g[min_idx][i]);
                    else // 该节点是第一次访问，直接更新
                        d[i] = min_val + g[min_idx][i];
                }
        }
        int res = 0;
        for(int i = 1; i <= N; i++)
        {
            if(d[i] == -1)
                return -1;
            res = max(res, d[i]);
        }
        return res;
    }
};

// floyd
// 350ms
class Solution_3 {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        // 邻接矩阵
        vector<vector<int> > g(N + 1, vector<int>(N + 1, -1));
        for(int i = 1; i <= N; ++i)
            g[i][i] = 0;
        for(int i = 0; i < (int)times.size(); i++)
            g[times[i][0]][times[i][1]] = times[i][2];

        // 遍历所有节点，k 表示使用k节点进行松弛
        for(int k = 1; k <= N; ++k)
            for(int i = 1; i <= N; ++i)
                for(int j = 1; j <= N; ++j)
                    // 使用 k 松弛 i -> j 的最短路径
                    if(g[i][k] != -1 && g[k][j] != -1)
                    {
                        if(g[i][j] != -1)
                            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
                        else
                            g[i][j] = g[i][k] + g[k][j];
                    }

        int result = 0;
        // 遍历 K 到所有节点的最短路径的最大值
        for(int i = 1; i <= N; ++i)
        {
            if(g[K][i] == -1)
                return -1;
            result = max(result, g[K][i]);
        }
        return result;
    }
};

// Bellman Ford
// 350ms
class Solution_5 {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        // 存放 K 到各个点的最短路径，最大的那个最短路径即为结果
        vector<int> d(N + 1, -1);
        d[K] = 0;

        // 进行 N - 1 轮松弛，因为任意两点间的最短路径最多包含 N - 1 条边
        for(int i = 1; i < N; ++i)
            for(vector<int> &edge: times)
            {
                int u = edge[0], v = edge[1], w = edge[2];
                // 判断能否通过 u -> v 缩短 d[v] (松弛)
                if(d[u] != -1 && (d[u] + w < d[v] || d[v] == -1))
                        d[v] = d[u] + w;
            }

        int result = 0;
        for(int i = 1; i <= N; ++i)
        {
            if(d[i] == -1)
                return -1;
            result = max(result, d[i]);
        }
        return result;
    }
};

// spfa
// 170ms
class Solution_6 {
public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
        vector<vector<int> > g(N + 1, vector<int>(N + 1, -1));
        for (int i = 1; i <= N; i++)
                g[i][i] = 0;
        for (vector<int> &time : times)
            g[time[0]][time[1]] = time[2];

        vector<int> d(N + 1, -1);
        d[K] = 0;

        queue<int, list<int> > q;
        q.push(K);

        while(!q.empty())
        {
            int cur = q.front();
            q.pop();
            for(int i = 1; i <= N; ++i)
            {
                if(g[cur][i] != -1 && (d[i] == -1 || d[i] > d[cur] + g[cur][i]))
                {
                    // 当最短距离发生变化且不在队列中时，将该节点加入队列
                    d[i] = d[cur] + g[cur][i];
                    q.push(i);
                }
            }
        }

        int result = 0;
        for(int i = 1; i <= N; ++i)
        {
            if(d[i] == -1)
                return -1;
            result = max(result, d[i]);
        }
        return result;
    }
};
