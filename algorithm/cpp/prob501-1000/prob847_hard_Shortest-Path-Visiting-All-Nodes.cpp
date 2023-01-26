// prob847: Shortest Path Visiting All Nodes

/*
 * An undirected, connected graph of N nodes (labeled 0, 1, 2, ..., N-1) is given as graph.
 * graph.length = N, and j != i is in the list graph[i] exactly once, if and only if nodes i and j are connected.
 * Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
 */

/*
 * Example 1:
 * Input: [[1,2,3],[0],[0],[0]]
 * Output: 4
 * Explanation: One possible path is [1,0,2,0,3]
 * Example 2:
 * Input: [[1],[0,2,4],[1,3,4],[2],[1,2]]
 * Output: 4
 * Explanation: One possible path is [0,1,4,2,3]
 */

/*
 * Note:
 * 1 <= graph.length <= 12
 * 0 <= graph[i].length < graph.length
 */

#include <vector>
#include <climits>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int N = graph.size();
        vector<vector<int> > d(N, vector<int>(N, INT_MAX / 2));
        for(int i = 0; i < N; ++i)
            for(int j: graph[i])
            {
                d[i][j] = 1;
                d[j][i] = 1;
            }
        for(int k = 0; k < N; ++k)
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

        int all_state = (1 << N) - 1;
        vector<vector<int> > dp(all_state + 1, vector<int>(N, INT_MAX / 2));
        for(int i = 0; i < N; ++i)
            dp[(1 << i)][i] = 0;
        for(int state = 0; state < (1 << N); ++state)
        {
            for(int j = 0; j < N; ++j)
            {
                if(state & (1 << j)) continue;
                for(int i = 0; i < N; ++i)
                {
                    if(!(state & (1 << i))) continue;
                    // i 在 state 中，j 不在 state 中
                    dp[state|(1 << j)][j] = min(dp[state|(1 << j)][j], dp[state][i] + d[i][j]);
                }
            }
        }

        int result = INT_MAX;
        for(int i = 0; i < N; ++i)
            result = min(result, dp[(1 << N) - 1][i]);

        return result;
    }

};
