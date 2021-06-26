// prob886: Possible Bipartition

/*
 * Given a set of N people (numbered 1, 2, ..., N), we would like to split everyone into two groups of any size.
 *
 * Each person may dislike some other people, and they should not go into the same group. 
 *
 * Formally, if dislikes[i] = [a, b], it means it is not allowed to put the people numbered a and b into the same group.
 *
 * Return true if and only if it is possible to split everyone into two groups in this way.
 */

/*
 * Example 1:
 *
 * Input: N = 4, dislikes = [[1,2],[1,3],[2,4]]
 * Output: true
 * Explanation: group1 [1,4], group2 [2,3]
 * Example 2:
 *
 * Input: N = 3, dislikes = [[1,2],[1,3],[2,3]]
 * Output: false
 * Example 3:
 *
 * Input: N = 5, dislikes = [[1,2],[2,3],[3,4],[4,5],[1,5]]
 * Output: false
 */

/*
 * Constraints:
 *
 * 1 <= N <= 2000
 * 0 <= dislikes.length <= 10000
 * dislikes[i].length == 2
 * 1 <= dislikes[i][j] <= N
 * dislikes[i][0] < dislikes[i][1]
 * There does not exist i != j for which dislikes[i] == dislikes[j].
 */

#include <vector>
#include <queue>

using namespace std;

// 建邻接表，调用 lc785
class Solution_785 {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        if(graph.empty()) return false;
        int n = graph.size();
        if(n == 1) return true;

        int st;
        queue<int> q;
        vector<int> d(n, 0);

        for(int i = 0; i < n; ++i)
        {
            if(d[i] == 0)
                st = i;
            q.push(st);
            d[st] = 1;
            while(!q.empty())
            {
                int u = q.front(); // 当前点
                q.pop();
                for(int v: graph[u])
                {
                    if(d[v] != 0)
                    {
                        if(!(d[u] ^ d[v]))
                            return false;
                        else
                            continue;
                    }
                    d[v] = -d[u];
                    q.push(v);
                }
            }
        }
        return true;
    }
};

class Solution {
public:
    bool possibleBipartition(int N, vector<vector<int>>& dislikes) {
        vector<vector<int>> g(N);
        for(const vector<int>& edge: dislikes)
        {
            g[edge[0] - 1].push_back(edge[1] - 1);
            g[edge[1] - 1].push_back(edge[0] - 1);
        }
        Solution_785 solution_785;
        return solution_785.isBipartite(g);
    }
};
