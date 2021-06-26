// prob675: Cut Off Trees for Golf Event

/*
 * You are asked to cut off trees in a forest for a golf event. The forest is represented as a non-negative 2D map, in this map:
 * 0 represents the obstacle can't be reached.
 * 1 represents the ground can be walked through.
 * The place with number bigger than 1 represents a tree can be walked through, and this positive number represents the tree's height.
 * In one step you can walk in any of the four directions top, bottom, left and right also when standing in a point which is a tree you can decide whether or not to cut off the tree.
 * You are asked to cut off all the trees in this forest in the order of tree's height - always cut off the tree with lowest height first. And after cutting, the original place has the tree will become a grass (value 1).
 * You will start from the point (0, 0) and you should output the minimum steps you need to walk to cut off all the trees. If you can't cut off all the trees, output -1 in that situation.
 * You are guaranteed that no two trees have the same height and there is at least one tree needs to be cut off.
 */

/*
 * Example 1:
 * Input:
 * [
 *  [1,2,3],
 *  [0,0,4],
 *  [7,6,5]
 * ]
 * Output: 6
 * Example 2:
 * Input:
 * [
 *  [1,2,3],
 *  [0,0,0],
 *  [7,6,5]
 * ]
 * Output: -1
 * Example 3:
 * Input:
 * [
 *  [2,3,4],
 *  [0,0,5],
 *  [8,7,6]
 * ]
 * Output: 6
 * Explanation: You started from the point (0,0) and you can cut off the tree in (0,0) directly without walking.
 */

/*
 * Constraints:
 * 1 <= forest.length <= 50
 * 1 <= forest[i].length <= 50
 * 0 <= forest[i][j] <= 10^9
 */

#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <stack>

using namespace std;


// HadLock 算法
// https://leetcode.com/problems/cut-off-trees-for-golf-event/discuss/107396/Python-solution-based-on-wufangjie's-(Hadlock's-algorithm)
/*
 * Just my own very similar implementation of @wufangjie's solution (and some terminology from the Hadlock algorithm which @awice mentioned to me), with some more explanation. Gets accepted in about 700 ms.
 *
 * Basically find the trees, sort them by order, find the distance from each tree to the next, and sum those distances. But how to find the distance from one cell to some other cell? BFS is far to slow for the current test suite. Instead use what's apparently known as "Hadlock's Algorithm" (though I've only seen high-level descriptions of that). First try paths with no detour (only try steps in the direction towards the goal), then if necessary try paths with one detour step, then paths with two detour steps, etc. The distance then is the Manhattan distance plus twice the number of detour steps (twice because you'll have to make up for a detour step with a later step back towards the goal).
 *
 * How to implement that?
 *
 * Round 1: Run a DFS only on cells that you can reach from the start cell with no detour towards the goal, i.e., only walking in the direction towards the goal. If this reaches the goal, we're done. Otherwise...
 * Round 2: Try again, but this time try starting from all those cells reachable with one detour step. Collect these in round 1.
 * Round 3: If round 2 fails, try again but start from all those cells reachable with two detour steps. Collect these in round 2.
 * And so on...
 * If there are no obstacles, then this directly walks a shortest path towards the goal, which is of course very fast. Much better than BFS which would waste time looking in all directions. With only a few obstacles, it's still close to optimal.
 *
 * My distance function does this searching algorithm. I keep the current to-be-searched cells in my now stack. When I move to a neighbor that's closer to the goal, I also put it in now. If it's not closer, then that's a detour step so I just remember it on my soon stack for the next round.
 */
// 900ms
// 英文版 700ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, forest[i][j]));
            }
        sort(trees.begin(), trees.end(), cmp); // O(MNlog(MN))

        // 是否所有的树都能走到 O(MN)
        // 记录所有能走到的点(一维形式) O(MN)
        unordered_set<int> reached;
        bfs(forest, reached);
        for(auto tree: trees)
            if(reached.find(tree.pos) == reached.end())
                return -1;

        // 所有树都走得到，结果一定不为 -1
        int result = 0;
        int prev = 0;
        vector<bool> visited, used;
        for(auto tree: trees)
        {
            visited.assign(m * n, false);
            used.assign(m * n, false);
            int d = dfs(prev, tree.pos, forest, visited, used);
            result += d;
            prev = tree.pos;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1}; // 右，左，下，上
    int dy[4] = {1, -1, 0, 0};
    using PII = pair<int, int>;

    int dfs(int pos1, const int pos, const vector<vector<int> >& forest, vector<bool>& visited, vector<bool>& used)
    {
        if(pos1 == pos) return 0;
        int n = forest.size(), m = forest[0].size();
        int x = pos / m, y = pos % m;

        int result = manhattan(pos1 / m, pos1 % m, x, y);
        // st2 始终比 st1 多一个 detours
        // 因为当前点始终从 st1 取，下一个新点如果要 detour，先放进 st2，不需要 detour 才直接进 st1
        // st1 空了才会把 st2 倒进 st1
        vector<int> st1, st2;
        st1.push_back(pos1);
        used[pos1] = true; // 已经见过的点
        visited[pos1] = true; // 已经使用的点
        int detours = 0;

        while(true)
        {
            if(st1.empty())
            {
                // 不增加 detours 到不了终点
                swap(st1, st2);
                for(int pos1: st1) used[pos1] = true;
                ++detours;
            }

            int pos1 = st1.back();
            st1.pop_back();
            if(pos1 == pos)
                break;

            int x1 = pos1 / m, y1 = pos1 % m;
            // 与目标方向一致的下一点进 st1, 与目标方向不一致的下一点进 st2
            // 新点若与目标方向一致则加入 visited 和 used，直接进入 st1
            // 新点若与目标方向不一致则只加入 visited，先加入 st2 暂存
            for(int d: positive_direction(x1, y1, x, y))
            {
                // (x1, y1) 朝着 (x, y) 的方向
                int x2 = x1 + dx[d], y2 = y1 + dy[d];
                if(x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
                if(forest[x2][y2] == 0) continue;
                int pos2 = x2 * m + y2;
                if(used[pos2]) continue;
                visited[pos2] = true;
                used[pos2] = true;
                st1.push_back(pos2);
            }
            for(int d: negative_direction(x1, y1, x, y))
            {
                // (x1, y1) 朝着 (x, y) 相反的方向
                int x2 = x1 + dx[d], y2 = y1 + dy[d];
                if(x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
                if(forest[x2][y2] == 0) continue;
                int pos2 = x2 * m + y2;
                if(visited[pos2]) continue;
                visited[pos2] = true;
                st2.push_back(pos2);
            }
        }

        return result + detours * 2;
    }

    vector<int> positive_direction(int x1, int y1, int x, int y)
    {
        // (x1, y1) 朝着 (x, y) 的方向
        vector<int> result;
        if(x1 > x) result.push_back(3); // 上
        if(x1 < x) result.push_back(2); // 下
        if(y1 > y) result.push_back(1); // 左
        if(y1 < y) result.push_back(0); // 右
        return result;
    }

    vector<int> negative_direction(int x1, int y1, int x, int y)
    {
        // (x1, y1) 朝着 (x, y) 相反的方向
        vector<int> result;
        if(x1 >= x) result.push_back(2); // 上
        if(x1 <= x) result.push_back(3); // 下
        if(y1 >= y) result.push_back(0); // 左
        if(y1 <= y) result.push_back(1); // 右
        return result;
    }

    void bfs(const vector<vector<int> >& forest, unordered_set<int>& reached)
    {
        int n = forest.size(), m = forest[0].size();
        vector<int> visited(m * n, false);
        visited[0] = true;
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int p = q.front();
            q.pop();
            reached.insert(p);
            for(int d = 0; d < 4; ++d)
            {
                int x = p / m + dx[d], y = (p % m) + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(forest[x][y] == 0) continue;
                int pos = x * m + y;
                if(visited[pos]) continue;
                visited[pos] = true;
                q.push(pos);
            }
        }
    }

    int manhattan(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }
};

// 优化：增加将 vector.assign 改为 memset (这次的 memset 的改变与下面的优化6相比收益很小)
// 804ms
// 英文版 668ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, forest[i][j]));
            }
        sort(trees.begin(), trees.end(), cmp); // O(MNlog(MN))

        // 是否所有的树都能走到 O(MN)
        // 记录所有能走到的点(一维形式) O(MN)
        unordered_set<int> reached;
        bool *visited = new bool[n * m];
        bfs(forest, reached, visited);
        for(auto tree: trees)
            if(reached.find(tree.pos) == reached.end())
                return -1;

        // 所有树都走得到，结果一定不为 -1
        int result = 0;
        int prev = 0;
        bool *used = new bool[n * m];
        for(auto tree: trees)
        {
            int d = dfs(prev, tree.pos, forest, visited, used);
            result += d;
            prev = tree.pos;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1}; // 右，左，下，上
    int dy[4] = {1, -1, 0, 0};
    using PII = pair<int, int>;

    int dfs(int pos1, const int pos, const vector<vector<int> >& forest, bool* visited, bool* used)
    {
        if(pos1 == pos) return 0;
        int n = forest.size(), m = forest[0].size();
        int x = pos / m, y = pos % m;

        int result = manhattan(pos1 / m, pos1 % m, x, y);
        // st2 始终比 st1 多一个 detours
        // 因为当前点始终从 st1 取，下一个新点如果要 detour，先放进 st2，不需要 detour 才直接进 st1
        // st1 空了才会把 st2 倒进 st1
        vector<int> st1, st2;
        st1.push_back(pos1);
        memset(visited, false, sizeof(bool) * n * m);
        memset(used, false, sizeof(bool) * n * m);
        used[pos1] = true; // 已经见过的点
        visited[pos1] = true; // 已经使用的点
        int detours = 0;

        while(true)
        {
            if(st1.empty())
            {
                // 不增加 detours 到不了终点
                swap(st1, st2);
                for(int pos1: st1) used[pos1] = true;
                ++detours;
            }

            int pos1 = st1.back();
            st1.pop_back();
            if(pos1 == pos)
                break;

            int x1 = pos1 / m, y1 = pos1 % m;
            // 与目标方向一致的下一点进 st1, 与目标方向不一致的下一点进 st2
            // 新点若与目标方向一致则加入 visited 和 used，直接进入 st1
            // 新点若与目标方向不一致则只加入 visited，先加入 st2 暂存
            for(int d: positive_direction(x1, y1, x, y))
            {
                // (x1, y1) 朝着 (x, y) 的方向
                int x2 = x1 + dx[d], y2 = y1 + dy[d];
                if(x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
                if(forest[x2][y2] == 0) continue;
                int pos2 = x2 * m + y2;
                if(used[pos2]) continue;
                visited[pos2] = true;
                used[pos2] = true;
                st1.push_back(pos2);
            }
            for(int d: negative_direction(x1, y1, x, y))
            {
                // (x1, y1) 朝着 (x, y) 相反的方向
                int x2 = x1 + dx[d], y2 = y1 + dy[d];
                if(x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) continue;
                if(forest[x2][y2] == 0) continue;
                int pos2 = x2 * m + y2;
                if(visited[pos2]) continue;
                visited[pos2] = true;
                st2.push_back(pos2);
            }
        }

        return result + detours * 2;
    }

    vector<int> positive_direction(int x1, int y1, int x, int y)
    {
        // (x1, y1) 朝着 (x, y) 的方向
        vector<int> result;
        if(x1 > x) result.push_back(3); // 上
        if(x1 < x) result.push_back(2); // 下
        if(y1 > y) result.push_back(1); // 左
        if(y1 < y) result.push_back(0); // 右
        return result;
    }

    vector<int> negative_direction(int x1, int y1, int x, int y)
    {
        // (x1, y1) 朝着 (x, y) 相反的方向
        vector<int> result;
        if(x1 >= x) result.push_back(2); // 上
        if(x1 <= x) result.push_back(3); // 下
        if(y1 >= y) result.push_back(0); // 左
        if(y1 <= y) result.push_back(1); // 右
        return result;
    }

    void bfs(const vector<vector<int> >& forest, unordered_set<int>& reached, bool* visited)
    {
        int n = forest.size(), m = forest[0].size();
        memset(visited, false, sizeof(bool) * n * m);
        visited[0] = true;
        queue<int> q;
        q.push(0);
        while(!q.empty())
        {
            int p = q.front();
            q.pop();
            reached.insert(p);
            for(int d = 0; d < 4; ++d)
            {
                int x = p / m + dx[d], y = (p % m) + dy[d];
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(forest[x][y] == 0) continue;
                int pos = x * m + y;
                if(visited[pos]) continue;
                visited[pos] = true;
                q.push(pos);
            }
        }
    }

    int manhattan(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }
};


// ------------------------------------------------

// 原始代码
// 中文版 TLE
// 英文版 1712ms 勉强过
struct Point
{
    int x, y;
    Point(int x, int y):x(x),y(y){}
};

struct Cmp
{
    vector<vector<int> > forest;
    Cmp(const vector<vector<int> >& forest):forest(forest){}
    bool operator()(const Point& point1, const Point& point2) const
    {
        return forest[point1.x][point1.y] < forest[point2.x][point2.y];
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp(forest);
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(cmp.forest[i][j] > 1)
                    trees.push_back(Point(i, j));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, 0), trees[i], cmp.forest, visited);
            else
                d = bfs(trees[i - 1], trees[i], cmp.forest, visited);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, Point p2, const vector<vector<int> >& forest, vector<vector<bool> >& visited)
    {
        if(p1.x == p2.x && p1.y == p2.y)
            return 0;
        int n = forest.size(), m = forest[0].size();
        queue<Point> q;
        visited.assign(n, vector<bool>(m, false));
        visited[p1.x][p1.y] = true;
        q.push(p1);
        vector<Point> level_nodes;
        int dist = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++dist;
            for(Point p: level_nodes)
            {
                for(int d = 0; d < 4; ++d)
                {
                    int x = p.x + dx[d], y = p.y + dy[d];
                    if(x == p2.x && y == p2.y)
                        return dist;
                    if(x < 0 || x >= n || y < 0 || y >= m) continue;
                    if(visited[x][y]) continue;
                    if(forest[x][y] == 0) continue;
                    visited[x][y] = true;
                    q.push(Point(x, y));
                }
            }
        }
        return -1;
    }
};

//----------------------------

// https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/solution/c-bfsjiu-ji-you-hua-chang-shu-400ms-shuang-bai-by-/
// 常数优化
// 优化点1 用自己的struct代替vector<int>作为queue内单元 效率提升100% queue里套vector<int>效率不是一般的低
// 优化点2 将2维数组展开到1维 效率提升60%
// 优化点3 memset代替重拷贝或重分配标记矩阵 效率提升40%
// 优化点4 标记提前到入队列时 效率提升无穷大 (原来习惯是遍历到在=true)
// 优化点5 剪枝 提前结束遍历

// 优化1：将 forest[i][j] 值加进 Point 字段，而不在 cmp 中持有 forest 矩阵
// 1944ms
// 英文版 1628 ms
struct Point
{
    int x, y, val;
    Point(int x, int y, int val):x(x),y(y),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(forest[i][j] > 1)
                    trees.push_back(Point(i, j, forest[i][j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, 0, forest[0][0]), trees[i], forest, visited);
            else
                d = bfs(trees[i - 1], trees[i], forest, visited);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, Point p2, const vector<vector<int> >& forest, vector<vector<bool> >& visited)
    {
        if(p1.x == p2.x && p1.y == p2.y)
            return 0;
        int n = forest.size(), m = forest[0].size();
        queue<Point> q;
        visited.assign(n, vector<bool>(m, false));
        visited[p1.x][p1.y] = true;
        q.push(p1);
        vector<Point> level_nodes;
        int dist = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++dist;
            for(Point p: level_nodes)
            {
                for(int d = 0; d < 4; ++d)
                {
                    int x = p.x + dx[d], y = p.y + dy[d];
                    if(x == p2.x && y == p2.y)
                        return dist;
                    if(x < 0 || x >= n || y < 0 || y >= m) continue;
                    if(visited[x][y]) continue;
                    if(forest[x][y] == 0) continue;
                    visited[x][y] = true;
                    q.push(Point(x, y, forest[x][y]));
                }
            }
        }
        return -1;
    }
};


// 优化2：将 Point 的 x, y 变成 pos (x * m + y)
// 1760ms
// 英文版 1392ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, forest[i][j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, forest[0][0]), trees[i], forest, visited);
            else
                d = bfs(trees[i - 1], trees[i], forest, visited);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, Point p2, const vector<vector<int> >& forest, vector<vector<bool> >& visited)
    {
        if(p1.pos == p2.pos)
            return 0;
        int n = forest.size(), m = forest[0].size();
        queue<Point> q;
        visited.assign(n, vector<bool>(m, false));
        visited[p1.pos / m][p1.pos % m] = true;
        q.push(p1);
        vector<Point> level_nodes;
        int dist = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++dist;
            for(Point p: level_nodes)
            {
                for(int d = 0; d < 4; ++d)
                {
                    int i = p.pos / m, j = p.pos % m;
                    int x = i + dx[d], y = j + dy[d];
                    int pos = x * m + y;
                    if(x < 0 || x >= n || y < 0 || y >= m) continue;
                    if(visited[x][y]) continue;
                    if(forest[x][y] == 0) continue;
                    if(pos == p2.pos) // 改成一维后，只能放在这里，不能放在前面
                        return dist;
                    visited[x][y] = true;
                    q.push(Point(pos, forest[x][y]));
                }
            }
        }
        return -1;
    }
};


// 优化3：将 visited 的索引从 x, y 变成 pos (x * m + y)
// 1396ms
// 英文版 1132ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, forest[i][j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        vector<bool> visited(n* m, false);
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, forest[0][0]), trees[i], forest, visited);
            else
                d = bfs(trees[i - 1], trees[i], forest, visited);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, Point p2, const vector<vector<int> >& forest, vector<bool>& visited)
    {
        if(p1.pos == p2.pos)
            return 0;
        int n = forest.size(), m = forest[0].size();
        queue<Point> q;
        visited.assign(n * m, false);
        visited[p1.pos] = true;
        q.push(p1);
        vector<Point> level_nodes;
        int dist = 0;
        while(!q.empty())
        {
            level_nodes.clear();
            while(!q.empty())
            {
                level_nodes.push_back(q.front());
                q.pop();
            }
            ++dist;
            for(Point p: level_nodes)
            {
                for(int d = 0; d < 4; ++d)
                {
                    int i = p.pos / m, j = p.pos % m;
                    int x = i + dx[d], y = j + dy[d];
                    int pos = x * m + y;
                    if(x < 0 || x >= n || y < 0 || y >= m) continue;
                    if(visited[pos]) continue;
                    if(forest[x][y] == 0) continue;
                    if(pos == p2.pos) // 改成一维后，只能放在这里，不能放在前面
                        return dist;
                    visited[pos] = true;
                    q.push(Point(pos, forest[x][y]));
                }
            }
        }
        return -1;
    }
};

// 优化4：在 bfs 阶段用 Point.val 作为距离用，节点自带距离后省去 level_nodes
// 1204ms
// 英文版 1096ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, forest[i][j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        vector<bool> visited(n* m, false);
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, 0), trees[i].pos, forest, visited);
            else
                d = bfs(Point(trees[i - 1].pos, 0), trees[i].pos, forest, visited);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, int p2_pos, const vector<vector<int> >& forest, vector<bool>& visited)
    {
        if(p1.pos == p2_pos)
            return 0;
        int n = forest.size(), m = forest[0].size();
        queue<Point> q;
        visited.assign(n * m, false);
        visited[p1.pos] = true;
        q.push(p1);
        while(!q.empty())
        {
            Point p = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int i = p.pos / m, j = p.pos % m;
                int x = i + dx[d], y = j + dy[d];
                int pos = x * m + y;
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(visited[pos]) continue;
                if(forest[x][y] == 0) continue;
                if(pos == p2_pos) // 改成一维后，只能放在这里，不能放在前面
                    return p.val + 1;
                visited[pos] = true;
                q.push(Point(pos, p.val + 1));
            }
        }
        return -1;
    }
};


// 优化5：将 forest 也变成 1 维
// 1160ms
// 英文版 960ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        vector<int> spread(m * n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                spread[i * m + j] = forest[i][j];
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, spread[i * m + j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        vector<bool> visited(n* m, false);
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, 0), trees[i].pos, spread, visited, m);
            else
                d = bfs(Point(trees[i - 1].pos, 0), trees[i].pos, spread, visited, m);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, int p2_pos, const vector<int>& forest, vector<bool>& visited, int m)
    {
        if(p1.pos == p2_pos)
            return 0;
        int n = forest.size() / m;
        queue<Point> q;
        visited.assign(n * m, false);
        visited[p1.pos] = true;
        q.push(p1);
        while(!q.empty())
        {
            Point p = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int i = p.pos / m, j = p.pos % m;
                int x = i + dx[d], y = j + dy[d];
                int pos = x * m + y;
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(visited[pos]) continue;
                if(forest[pos] == 0) continue;
                if(pos == p2_pos) // 改成一维后，只能放在这里，不能放在前面
                    return p.val + 1;
                visited[pos] = true;
                q.push(Point(pos, p.val + 1));
            }
        }
        return -1;
    }
};

// 优化6：visited.assign 改成 memset(收益极高)
// 640ms
// 英文版 496ms
struct Point
{
    int pos, val;
    Point(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Point& point1, const Point& point2) const
    {
        return point1.val < point2.val;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Point> trees;
        vector<int> spread(m * n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                spread[i * m + j] = forest[i][j];
                if(forest[i][j] > 1)
                    trees.push_back(Point(i * m + j, spread[i * m + j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        bool *visited = new bool[n * m]; // 动态数组只能开在堆上，因为 m, n 编译时不确定
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
                d = bfs(Point(0, 0), trees[i].pos, spread, visited, m);
            else
                d = bfs(Point(trees[i - 1].pos, 0), trees[i].pos, spread, visited, m);
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    int bfs(Point p1, int p2_pos, const vector<int>& forest, bool* visited, int m)
    {
        if(p1.pos == p2_pos)
            return 0;
        int n = forest.size() / m;
        queue<Point> q;
        memset(visited, false, sizeof(bool) * n * m);
        visited[p1.pos] = true;
        q.push(p1);
        while(!q.empty())
        {
            Point p = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int i = p.pos / m, j = p.pos % m;
                int x = i + dx[d], y = j + dy[d];
                int pos = x * m + y;
                if(x < 0 || x >= n || y < 0 || y >= m) continue;
                if(visited[pos]) continue;
                if(forest[pos] == 0) continue;
                if(pos == p2_pos) // 改成一维后，只能放在这里，不能放在前面
                    return p.val + 1;
                visited[pos] = true;
                q.push(Point(pos, p.val + 1));
            }
        }
        return -1;
    }
};


// 暂未使用办法
// https://leetcode-cn.com/problems/cut-off-trees-for-golf-event/solution/c-160ms-ti-jie-xi-shuo-chang-shu-you-hua-na-xie-sh/
// 优化1：快速 BFS(四周填充 0)
// 优化 2：手写队列
// 优化 3：间隔 BFS

// --------------------------------------------------------------------------------------------

// Astar
struct Tree
{
    int pos, val;
    Tree(int pos, int val):pos(pos),val(val){}
};

struct Cmp
{
    bool operator()(const Tree& point1, const Tree& point2) const
    {
        return point1.val < point2.val;
    }
};

struct AstarPoint
{
    int pos;
    int g;
    int f, h;
    AstarPoint(int pos, int g, int h=-1):pos(pos),g(g),h(h)
    {
        f = g + h;
    }
};

struct AstarCmp
{
    bool operator()(const AstarPoint& point1, const AstarPoint& point2) const
    {
        return point1.f > point2.f;
    }
};

class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if(forest[0][0] == 0) return -1;
        int n = forest.size(), m = forest[0].size();
        Cmp cmp;
        vector<Tree> trees;
        vector<int> spread(m * n);
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                spread[i * m + j] = forest[i][j];
                if(forest[i][j] > 1)
                    trees.push_back(Tree(i * m + j, spread[i * m + j]));
            }
        sort(trees.begin(), trees.end(), cmp);

        int ntree = trees.size();
        int result = 0;
        bool *visited = new bool[n * m]; // 动态数组只能开在堆上，因为 m, n 编译时不确定
        for(int i = 0; i < ntree; ++i)
        {
            int d;
            if(i == 0)
            {
                AstarPoint s(0, 0, h(0, trees[i].pos, m));
                d = bfs(s, trees[i].pos, spread, visited, m);
            }
            else
            {
                AstarPoint s(trees[i - 1].pos, 0, h(trees[i - 1].pos, trees[i].pos, m));
                d = bfs(s, trees[i].pos, spread, visited, m);
            }
            if(d == -1)
                return -1;
            result += d;
        }
        return result;
    }

private:
    int bfs(AstarPoint p1, int p2_pos, const vector<int>& forest, bool* visited, int m)
    {
        if(p1.pos == p2_pos)
            return 0;
        int N = forest.size();
        priority_queue<AstarPoint, vector<AstarPoint>, AstarCmp> pq;
        memset(visited, false, sizeof(bool) * N);
        visited[p1.pos] = true;
        pq.push(p1);
        int d[4] = {1, -1, m, -m}; // m 为矩阵的列数
        while(!pq.empty())
        {
            AstarPoint p = pq.top();
            pq.pop();
            if(p.pos == p2_pos) // 改成一维后，只能放在这里，不能放在前面
                return p.g;
            visited[p.pos] = true;
            int py = p.pos % m;
            for(int i = 0; i < 4; ++i)
            {
                if(py == 0 && i == 1) continue;
                if(py == m - 1 && i == 0) continue;
                int pos = p.pos + d[i];
                if(pos < 0 || pos >= N) continue;
                if(visited[pos]) continue;
                if(forest[pos] == 0) continue;
                AstarPoint nxt(pos, p.g + 1, h(pos, p2_pos, m));
                pq.push(nxt);
            }
        }
        return -1;
    }

    int h(int pos, int t, int m)
    {
        int h = abs(pos / m - t / m);
        int w = abs(pos % m - t % m);
        return w + h;
    }
};
