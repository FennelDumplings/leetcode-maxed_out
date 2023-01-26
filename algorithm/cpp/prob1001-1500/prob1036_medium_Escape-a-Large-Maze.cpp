// prov1036: Escape a Large Maze

/*
 * In a 1 million by 1 million grid, the coordinates of each grid square are (x, y) with 0 <= x, y < 10^6.
 * We start at the source square and want to reach the target square.  Each move, we can walk to a 4-directionally
 * adjacent square in the grid that isn't in the given list of blocked squares.
 * Return true if and only if it is possible to reach the target square through a sequence of moves.
 */

/*
 * Example 1:
 * Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
 * Output: false
 * Explanation:
 * The target square is inaccessible starting from the source square, because we can't walk outside the grid.
 * Example 2:
 * Input: blocked = [], source = [0,0], target = [999999,999999]
 * Output: true
 * Explanation:
 * Because there are no blocked cells, it's possible to reach the target square.
 */

/*
 * Note:
 * 0 <= blocked.length <= 200
 * blocked[i].length == 2
 * 0 <= blocked[i][j] < 10^6
 * source.length == target.length == 2
 * 0 <= source[i][j], target[i][j] < 10^6
 * source != target
 */

#include <vector>
#include <set>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

// 有限 BFS, (BFS提前退出)
using PII = pair<int, int>;
struct MyHash {
    size_t operator() (const PII& v) const {
        return hash<int>()(v.first) ^ hash<int>()(v.second);
    }
};

class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        unordered_set<PII, MyHash> block;
        for(vector<int> &b: blocked) block.insert({b[0], b[1]});
        return bfs(block, source, target) && bfs(block, target, source);
    }

private:
    bool bfs(unordered_set<PII, MyHash>& blocked, vector<int>& source, vector<int>& target)
    {
        int n = 1000000, m = 1000000;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        unordered_set<PII, MyHash> visited;
        queue<PII> q;
        int max_step = blocked.size() * (blocked.size() - 1) / 2;
        q.push({source[0], source[1]});
        visited.insert({source[0], source[1]});
        int step = 1;
        while(!q.empty())
        {
            PII cur = q.front();
            q.pop();
            if(step > max_step)
                return true;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur.first + dx[d], y = cur.second + dy[d];
                if(x == target[0] && y == target[1])
                    return true;
                if(_check(x, y, n, m) && visited.find({x, y}) == visited.end()
                        && blocked.find({x, y}) == blocked.end())
                {
                    q.push({x, y});
                    visited.insert({x, y});
                    ++step;
                }
            }
        }
        return false;
    }

    bool _check(int i, int j, int n, int m)
    {
        return i >= 0 && i < n && j >= 0 && j < m;
    }
};


// 有限 BFS, (BFS提前退出)
// vector<int> 表示点比 PII 慢不少
struct MyHash2 {
    size_t operator() (const vector<int>& v) const {
        size_t h = 0;
        for (auto vv : v) h ^= hash<int>()(vv);
        return h;
    }
};

class Solution2 {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        unordered_set<vector<int>, MyHash> block(blocked.begin(), blocked.end());
        return bfs(block, source, target) && bfs(block, target, source);
    }

private:
    bool bfs(unordered_set<vector<int>, MyHash2>& blocked, vector<int>& source, vector<int>& target)
    {
        int n = 1000000, m = 1000000;
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        unordered_set<vector<int>, MyHash2> visited;
        queue<vector<int> > q;
        int max_step = blocked.size() * (blocked.size() - 1) / 2;
        q.push(vector<int>({source[0], source[1]}));
        visited.insert(vector<int>({source[0], source[1]}));
        int step = 1;
        while(!q.empty())
        {
            vector<int> cur = q.front();
            q.pop();
            if(step > max_step)
                return true;
            for(int d = 0; d < 4; ++d)
            {
                int x = cur[0] + dx[d], y = cur[1] + dy[d];
                if(x == target[0] && y == target[1])
                    return true;
                if(_check(x, y, n, m) && visited.find(vector<int>{x, y}) == visited.end()
                        && blocked.find(vector<int>{x, y}) == blocked.end())
                {
                    q.push(vector<int>({x, y}));
                    visited.insert(vector<int>{x, y});
                    ++step;
                }
            }
        }
        return false;
    }

    bool _check(int i, int j, int n, int m)
    {
        return i >= 0 && i < n && j >= 0 && j < m;
    }
};

// 离散化
class Solution_2 {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        vector<int> x, y;
        unordered_set<int> set_x, set_y;
        int left = 0, up = 0, right = 1000000 - 1, down = 1000000 - 1;
        blocked.push_back(source);
        blocked.push_back(target);
        for(const vector<int> block: blocked)
        {
            int i = block[0], j = block[1];
            for(int k = i - 1; k <= i + 1; ++k)
            {
                if(k < up || k > down) continue;
                if(set_x.find(k) == set_x.end())
                {
                    x.push_back(k);
                    set_x.insert(k);
                }
            }
            for(int k = j - 1; k <= j + 1; ++k)
            {
                if(k < left || k > right) continue;
                if(set_y.find(k) == set_y.end())
                {
                    y.push_back(k);
                    set_y.insert(k);
                }
            }
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        x.erase(unique(x.begin(), x.end()), x.end());
        y.erase(unique(y.begin(), y.end()), y.end());
        int n = x.size(), m = y.size();
        vector<vector<int> > grid(n, vector<int>(m, 0));
        for(const vector<int> block: blocked)
        {
            int i = block[0], j = block[1];
            int new_i = _find(i, x);
            int new_j = _find(j, y);
            grid[new_i][new_j] = 1;
        }
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        vector<vector<bool> > visited(n, vector<bool>(m, false));
        queue<vector<int> > q;
        int s_x = _find(source[0], x), s_y = _find(source[1], y);
        int e_x = _find(target[0], x), e_y = _find(target[1], y);
        q.push(vector<int>({s_x, s_y}));
        visited[s_x][s_y] = true;
        while(!q.empty())
        {
            vector<int> cur = q.front();
            q.pop();
            for(int d = 0; d < 4; ++d)
            {
                int xx = cur[0] + dx[d], yy = cur[1] + dy[d];
                if(xx == e_x && yy == e_y)
                    return true;
                if(_check(xx, yy, n, m) && grid[xx][yy] == 0 && !visited[xx][yy])
                {
                    q.push(vector<int>({xx, yy}));
                    visited[xx][yy] = true;
                }
            }
        }
        return false;
    }

private:
    int _find(int v, const vector<int>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin();
    }

    bool _check(int i, int j, int n, int m)
    {
        return i >= 0 && i < n && j >= 0 && j < m;
    }
};
