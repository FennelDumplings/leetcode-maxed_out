// prob913: Cat and Mouse

/*
 * A game on an undirected graph is played by two players, Mouse and Cat, who alternate turns.
 * The graph is given as follows: graph[a] is a list of all nodes b such that ab is an edge of the graph.
 * Mouse starts at node 1 and goes first, Cat starts at node 2 and goes second, and there is a Hole at node 0.
 * During each player's turn, they must travel along one edge of the graph that meets where they are.  For example,
 * if the Mouse is at node 1, it must travel to any node in graph[1].
 * Additionally, it is not allowed for the Cat to travel to the Hole (node 0.)
 * Then, the game can end in 3 ways:
 * If ever the Cat occupies the same node as the Mouse, the Cat wins.
 * If ever the Mouse reaches the Hole, the Mouse wins.
 * If ever a position is repeated (ie. the players are in the same position as a previous turn, and it is the same player's
 * turn to move), the game is a draw.
 * Given a graph, and assuming both players play optimally, return 1 if the game is won by Mouse, 2 if the game is won by Cat,
 * and 0 if the game is a draw.
 */

/*
 * Note:
 * 3 <= graph.length <= 50
 * It is guaranteed that graph[1] is non-empty.
 * It is guaranteed that graph[2] contains a non-zero element. 
 */

/*
 * Example 1:
 * Input: [[2,5],[3],[0,4,5],[1,4,5],[2,3],[0,2,3]]
 * Output: 0
 * Explanation:
 * 4---3---1
 * |   |
 * 2---5
 *  \ /
 *   0
 */

#include <vector>
#include <queue>

using namespace std;

// minimax + 记忆化递归
// ref: https://www.acwing.com/solution/LeetCode/content/556/
class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<vector<int> > > dp(2 * n, vector<vector<int>>(n, vector<int>(n, -1)));
        return solve(graph, 0, 1, 2, dp);
    }

private:
    int solve(const vector<vector<int>>& graph, int t, int m, int c, vector<vector<vector<int> > >& dp)
    {
        if (t == (int)graph.size() * 2)
            return 0;
        if (m == c)
            return dp[t][m][c] = 2;
        if (m == 0)
            return dp[t][m][c] = 1;
        if (dp[t][m][c] != -1)
            return dp[t][m][c];


        bool flag;
        if (t % 2 == 0)
        {
            // 轮到鼠走
            flag = true;
            for (int i = 0; i < (int)graph[m].size(); i++)
            {
                int nxt = solve(graph, t + 1, graph[m][i], c, dp);
                if (nxt == 1)
                    return dp[t][m][c] = 1;
                else if (nxt != 2)
                    flag = false;
            }
            if (flag)
                return dp[t][m][c] = 2;
            else
                return dp[t][m][c] = 0;
        }
        else
        {
            // 轮到猫走
            flag = true;
            for (int i = 0; i < (int)graph[c].size(); i++)
                if (graph[c][i] != 0) {
                    int nxt = solve(graph, t + 1, m, graph[c][i], dp);
                    if (nxt == 2)
                        return dp[t][m][c] = 2;
                    else if (nxt != 1)
                        flag = false;
                }
            if (flag)
                return dp[t][m][c] = 1;
            else
                return dp[t][m][c] = 0;
        }
    }
};

// minimax + BFS
class Solution_2 {
public:
    int catMouseGame(vector<vector<int> >& graph) {
        int N = graph.size();
        const int DRAW = 0, MOUSE = 1, CAT = 2;

        vector<vector<vector<int> > > color(N, vector<vector<int> >(N, vector<int>(3)));
        vector<vector<vector<int> > > draw_degree(N, vector<vector<int> >(N, vector<int>(3))); // 标记为 DRAW 的子节点个数

        // draw_degree[node] := 节点的子节点个数
        for(int m = 0; m < N; ++m)
            for(int c = 0; c < N; ++c)
            {
                draw_degree[m][c][1] = graph[m].size(); // t = 0, 轮鼠动
                draw_degree[m][c][2] = graph[c].size(); // t = 1, 轮猫动
                for(int x: graph[c])
                {
                    if(x == 0) // 猫无法移动到洞里
                    {
                        draw_degree[m][c][2]--;
                        break;
                    }
                }
            }

        // 将初始时胜负已知的点染色，并进队
        queue<vector<int> > q;
        for(int i = 0; i < N; ++i)
            for(int t = 1; t <= 2; ++t)
            {
                color[0][i][t] = MOUSE;
                q.push(vector<int>({0, i, t, MOUSE}));
                if(i > 0)
                {
                    color[i][i][t] = CAT;
                    q.push(vector<int>({i, i, t, CAT}));
                }
            }

        // BFS过程
        while(!q.empty())
        {
            vector<int> node = q.front();
            q.pop();
            int i = node[0], j = node[1], t = node[2], c = node[3]; // c 颜色
            for(vector<int> parent: _parents(graph, i, j, t))
            {
                int i2 = parent[0], j2 = parent[1], t2 = parent[2];
                if(color[i2][j2][t2] == DRAW)
                {
                    if(t2 == c)
                    {
                        // 父状态节点可以做必胜移动：
                        // 出队状态颜色是猫胜且父节点轮猫走
                        // 出队状态颜色是鼠胜且父节点轮鼠走
                        color[i2][j2][t2] = c;
                        q.push(vector<int>({i2, j2, t2, c}));
                    }
                    else // 当前轮到行动的角色与出队节点的颜色相反
                    {
                        draw_degree[i2][j2][t2]--; // 该父节点又有了一个子节点(出队节点v)不标记为 DRAW
                        if(draw_degree[i2][j2][t2] == 0)
                        {
                            color[i2][j2][t2] = 3 - t2;
                            q.push(vector<int>({i2, j2, t2, 3 - t2}));
                        }
                    }
                }
            }
        }
        return color[1][2][1];
    }

private:
    // 哪些状态节点可以转移到 (m, n, t)
    vector<vector<int> > _parents(vector<vector<int> >& graph, int m, int c, int t)
    {
        vector<vector<int> > result;
        if(t == 2) // 轮猫动, 上一轮轮猫动
        {
            for(int m2: graph[m])
                result.push_back(vector<int>({m2, c, 3 - t}));
        }
        else // 轮鼠动，上一轮轮猫动
        {
            for(int c2: graph[c])
                if(c2 > 0)
                    result.push_back(vector<int>({m, c2, 3 - t}));
        }
        return result;
    }
};
