// prob778: Swim in Rising Water

/*
 * On an N x N grid, each square grid[i][j] represents the elevation at that point (i,j).
 * Now rain starts to fall. At time t, the depth of the water everywhere is t. You can swim from a square to another 4-directionally
 * adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distance in
 * zero time. Of course, you must stay within the boundaries of the grid during your swim.
 * You start at the top left square (0, 0). What is the least time until you can reach the bottom right square (N-1, N-1)?
 */

/*
 * Example 1:
 * Input: [[0,2],[1,3]]
 * Output: 3
 * Explanation:
 * At time 0, you are in grid location (0, 0).
 * You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
 * You cannot reach point (1, 1) until time 3.
 * When the depth of water is 3, we can swim anywhere inside the grid.
 * Example 2:
 * Input: [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
 * Output: 16
 * Explanation:
 *  0  1  2  3  4
 *  24 23 22 21  5
 *  12 13 14 15 16
 *  11 17 18 19 20
 *  10  9  8  7  6
 *  The final route is marked in bold.
 *  We need to wait until time 16 so that (0, 0) and (4, 4) are connected.
 */

/*
 * Note:
 * 2 <= N <= 50.
 * grid[i][j] is a permutation of [0, ..., N*N - 1].
 */

#include <vector>
#include <queue>

using namespace std;

// 优先级队列 BFS
struct Node
{
    int x, y, h;
    Node(int i, int j, int height):x(i),y(j),h(height){}
};

struct Cmp
{
    bool operator() (const Node& node1, const Node& node2)
    {
        return node1.h > node2.h; // 小顶堆
    }
};

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size(); // 调用方保证 N >= 2
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        priority_queue<Node, vector<Node>, Cmp> pq;
        vector<vector<bool> > visited(N, vector<bool>(N, false));
        // 记录到达 grid[N - 1][N - 1] 经过路线的最大高度, 和最小高度
        int maxh = grid[0][0];
        visited[0][0] = true;
        pq.push(Node(0, 0, grid[0][0]));
        while(!pq.empty())
        {
            Node cur = pq.top();
            pq.pop();
            maxh = max(maxh, cur.h);
            if(cur.x == N - 1 && cur.y == N - 1)
                return maxh;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.x + dx[d];
                int y = cur.y + dy[d];
                if(!_check(x, y, N) || visited[x][y])
                    continue;
                pq.push(Node(x, y, grid[x][y]));
                visited[x][y] = true;
            }
        }
        return -1;
    }

private:
    bool _check(int x, int y, int N)
    {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
};

// 折半枚举 + DFS (值域二分)
class Solution_2 {
public:
    int swimInWater(vector<vector<int>>& grid) {
        int N = grid.size();
        int left = 0, right = N * N - 1;
        vector<vector<bool> > visited(N, vector<bool>(N, false));
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(grid[0][0] > mid)
            {
                left = mid + 1;
                continue;
            }
            visited.clear();
            visited.assign(N, vector<bool>(N, false));
            visited[0][0] = true;
            if(dfs(grid, visited, 0, 0, mid, N))
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }

private:
    bool dfs(const vector<vector<int> >& grid, vector<vector<bool> >& visited, int i, int j, int max_h, int N)
    {
        if(i == N - 1 && j == N - 1)
            return true;
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        for(int d = 0; d < 4; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(!_check(x, y, N) || visited[x][y] || grid[x][y] > max_h)
                continue;
            visited[x][y] = true;
            if(dfs(grid, visited, x, y, max_h, N))
                return true;
        }
        return false;
    }

    bool _check(int x, int y, int N)
    {
        return x >= 0 && x < N && y >= 0 && y < N;
    }
};
