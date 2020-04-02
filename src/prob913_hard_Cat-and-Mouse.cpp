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
    int solve(const vector<vector<int>>& graph, int t, int x, int y, vector<vector<vector<int> > >& dp)
    {
        if (t == (int)graph.size() * 2)
            return 0;
        if (x == y)
            return dp[t][x][y] = 2;
        if (x == 0)
            return dp[t][x][y] = 1;
        if (dp[t][x][y] != -1)
            return dp[t][x][y];


        int who = t % 2;
        bool flag;
        if (who == 0)
        { // Mouse goes next
            flag = true; // All ways are 2
            for (int i = 0; i < (int)graph[x].size(); i++)
            {
                int nxt = solve(graph, t + 1, graph[x][i], y, dp);
                if (nxt == 1)
                    return dp[t][x][y] = 1;
                else if (nxt != 2)
                    flag = false;
            }
            if (flag)
                return dp[t][x][y] = 2;
            else
                return dp[t][x][y] = 0;
        }
        else
        { // Cat goes next
            flag = true; // All ways are 1
            for (int i = 0; i < (int)graph[y].size(); i++)
                if (graph[y][i] != 0) {
                    int nxt = solve(graph, t + 1, x, graph[y][i], dp);
                    if (nxt == 2)
                        return dp[t][x][y] = 2;
                    else if (nxt != 1)
                        flag = false;
                }
            if (flag)
                return dp[t][x][y] = 1;
            else
                return dp[t][x][y] = 0;
        }
    }
};

// minimax + BFS
class Solution_2 {
public:
    int catMouseGame(vector<vector<int> >& graph) {
        int N = graph.size();
        int DRAW = 0, MOUSE = 1, CAT = 2;

        vector<vector<vector<int> > > color(N, vector<vector<int> >(N, vector<int>(3)));
        vector<vector<vector<int> > > degree(N, vector<vector<int> >(N, vector<int>(3)));

        // degree[node] := the number of neutral children of this node
        for(int m = 0; m < N; ++m)
            for(int c = 0; c < N; ++c)
            {
                degree[m][c][1] = graph[m].size(); // z = 1, 轮鼠动
                degree[m][c][2] = graph[c].size(); // z = 2, 轮猫动
                for(int x: graph[c])
                {
                    if(x == 0)
                    {
                        degree[m][c][2]--;
                        break;
                    }
                }
            }

        // enqueued : all nodes that are colored
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
        // percolate 渗透
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
                        // if the parent can make a winning move (ie. mouse to MOUSE), do so
                        color[i2][j2][t2] = c;
                        q.push(vector<int>({i2, j2, t2, c}));
                    }
                    else
                    {
                        degree[i2][j2][t2]--;
                        if(degree[i2][j2][t2] == 0)
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
    // What nodes could play their turn to
    // arrive at node (m, c, t) ?
    vector<vector<int> > _parents(vector<vector<int> >& graph, int m, int c, int t)
    {
        vector<vector<int> > result;
        if(t == 2)
        {
            for(int m2: graph[m])
                result.push_back(vector<int>({m2, c, 3 - t}));
        }
        else
        {
            for(int c2: graph[c])
                if(c2 > 0)
                    result.push_back(vector<int>({m, c2, 3 - t}));
        }
        return result;
    }
};
