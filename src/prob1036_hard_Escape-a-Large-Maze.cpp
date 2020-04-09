// prob1036: Escape a Large Maze

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

using namespace std;

// 二维离散化
struct MyHash {
    size_t operator() (const vector<int>& v) const {
        size_t h = 0;
        for (auto vv : v) h ^= hash<int>()(vv);
        return h;
    }
};


class Solution {
public:
    bool isEscapePossible(vector<vector<int>>& blocked, vector<int>& source, vector<int>& target) {
        set<int> rows;
        rows.insert(source[0]);
        rows.insert(target[0]);
        set<int> cols;
        cols.insert(source[1]);
        cols.insert(target[1]);
        unordered_set<vector<int>, MyHash> visited;
        for (auto b : blocked) {
            rows.insert(b[0]);
            if (b[0] - 1 >= 0) rows.insert(b[0] - 1);
            if (b[0] + 1 < 1e6) rows.insert(b[0] + 1);
            cols.insert(b[1]);
            if (b[1] - 1 >= 0) cols.insert(b[1] - 1);
            if (b[1] + 1 < 1e6) cols.insert(b[1] + 1);
            visited.insert(b);
        }
        vector<int> rs(rows.begin(), rows.end());
        vector<int> cs(cols.begin(), cols.end());
        if (visited.find(source) != visited.end()) return false;
        visited.insert(source);
        int i = lower_bound(rs.begin(), rs.end(), source[0]) - rs.begin();
        int j = lower_bound(cs.begin(), cs.end(), source[1]) - cs.begin();
        int ti = lower_bound(rs.begin(), rs.end(), target[0]) - rs.begin();
        int tj = lower_bound(cs.begin(), cs.end(), target[1]) - cs.begin();
        queue<vector<int>> q;
        q.push({i, j});
        while (!q.empty()) {
            int i = q.front()[0];
            int j = q.front()[1];
            q.pop();
            if (i == ti && j == tj) return true;
            // up
            if (i-1 >= 0) {
                if (visited.find({rs[i-1], cs[j]}) == visited.end()) {
                    visited.insert({rs[i-1], cs[j]});
                    q.push({i-1, j});
                }
            }
            // down
            if (i+1 < rs.size()) {
                if (visited.find({rs[i+1], cs[j]}) == visited.end()) {
                    visited.insert({rs[i+1], cs[j]});
                    q.push({i+1, j});
                }
            }
            // left
            if (j-1 >= 0) {
                if (visited.find({rs[i], cs[j-1]}) == visited.end()) {
                    visited.insert({rs[i], cs[j-1]});
                    q.push({i, j-1});
                }
            }
            // right
            if (j+1 < cs.size()) {
                if (visited.find({rs[i], cs[j+1]}) == visited.end()) {
                    visited.insert({rs[i], cs[j+1]});
                    q.push({i, j+1});
                }
            }
        }
        return false;
    }

};
