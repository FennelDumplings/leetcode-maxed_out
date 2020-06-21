// 20200621
// 4. 找到最小生成树里的关键边和伪关键边

/*
 * 给你一个 n 个点的带权无向连通图，节点编号为 0 到 n-1 ，同时还有一个数组 edges ，其中 edges[i] = [fromi, toi, weighti] 表示在 fromi 和 toi 节点之间有一条带权无向边。最小生成树 (MST) 是给定图中边的一个子集，它连接了所有节点且没有环，而且这些边的权值和最小。
 *
 * 请你找到给定图中最小生成树的所有关键边和伪关键边。如果最小生成树中删去某条边，会导致最小生成树的权值和增加，那么我们就说它是一条关键边。伪关键边则是可能会出现在某些最小生成树中但不会出现在所有最小生成树中的边。
 *
 * 请注意，你可以分别以任意顺序返回关键边的下标和伪关键边的下标。
 */

#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        int min_cost = prim(n, edges);
        cout << min_cost << endl;
        return {};

    }

private:
    int prim(int N, vector<vector<int>>& connections) {
        vector<vector<vector<int> > > g(N);
        for(const vector<int> &connection: connections)
        {
            int x = connection[0], y = connection[1], w = connection[2];
            g[x].push_back(vector<int>({w, y}));
            g[y].push_back(vector<int>({w, x}));
        }
        priority_queue<vector<int> > pq;
        pq.push({0, 1});
        vector<int> visited(N + 1, false);
        visited[0] = true;
        int cost = 0;
        while(!pq.empty())
        {
            vector<int> cur = pq.top();
            pq.pop();
            if(visited[cur[1]])
                continue;
            visited[cur[1]] = true;
            cost += -cur[0];
            for(vector<int> son: g[cur[1]])
            {
                if(visited[son[1]])
                    continue;
                pq.push({-son[0], son[1]});
            }
        }
        for(bool v: visited)
            if(!v)
                return -1;
        return cost;
    }

};


