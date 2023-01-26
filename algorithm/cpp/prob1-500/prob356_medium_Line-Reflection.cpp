// prob356: Line Reflection

/*
 * Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points symmetrically,
 * in other words, answer whether or not if there exists a line that after reflecting all points over the given line the
 * set of the original points is the same that the reflected ones.
 * Note that there can be repeated points.
 */

/*
 * Follow up:
 * Could you do better than O(n2) ?
 */

/*
 * Example 1:
 * Input: points = [[1,1],[-1,1]]
 * Output: true
 * Explanation: We can choose the line x = 0.
 * Example 2:
 * knput: points = [[1,1],[-1,-1]]
 * Output: false
 * Explanation: We can't choose a line.
 */

/*
 * Constraints:
 * n == points.length
 * 1 <= n <= 10^4
 * -10^8 <= points[i][j] <= 10^8
 */

#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <climits>

using namespace std;

class Solution {
public:
    bool isReflected(vector<vector<int>>& points) {
        vector<pair<int, unordered_set<int> > > verticle_points; // {a, b}, a: x, b: y 的列表，y 从小到大排序
        unordered_map<int, int> mapping; // x -> idx
        for(const vector<int>& point: points)
        {
            if(mapping.find(point[0]) != mapping.end())
                verticle_points[mapping[point[0]]].second.insert(point[1]);
            else
            {
                verticle_points.push_back(PIUI(point[0], unordered_set<int>({point[1]})));
                mapping[point[0]] = verticle_points.size() - 1;
            }
        }
        int n = verticle_points.size();
        if(n == 1) return true;
        sort(verticle_points.begin(), verticle_points.end(), Cmp());
        int left_side = verticle_points[0].first;
        int right_side = verticle_points[n - 1].first;
        int right = n - 1, left = 0;
        while(left < right)
        {
            int x1 = verticle_points[left].first;
            int x2 = verticle_points[right].first;
            unordered_set<int> &points1 = verticle_points[left].second;
            unordered_set<int> &points2 = verticle_points[right].second;
            if(!equal(points1.begin(), points1.end(), points2.begin()))
                return false;
            if(x1 - left_side != right_side - x2)
                return false;
            ++left;
            --right;
        }
        if(left > right)
            return true;
        return verticle_points[left].first - left_side == right_side - verticle_points[left].first;
    }

private:
    using PIUI = pair<int, unordered_set<int>>;

    struct Cmp
    {
        bool operator()(const PIUI& verticle_points1, const PIUI& verticle_points2)
        {
            return verticle_points1.first < verticle_points2.first;
        }
    };
};

// 先求集合左右边界，找到可能的中线，然后对集合内所有点按所在行验证是否有中线的对称点。
// 因为坐标没有重复，所以可以直接放set里。
// 不用排序
class Solution_2 {
public:
    bool isReflected(vector<vector<int>>& points) {
        unordered_map<int, unordered_set<int> > mapping;
        int left_side = INT_MAX, right_side = INT_MIN;
        for(const vector<int>& point: points)
        {
            left_side = min(left_side, point[0]);
            right_side = max(right_side, point[0]);
            mapping[point[1]].insert(point[0]);
        }
        int sum = left_side + right_side;
        for(const PIUSI& y_xs: mapping)
        {
            const unordered_set<int> &xs = y_xs.second;
            for(int x: xs)
                if(xs.find(sum - x) == xs.end())
                    return false;
        }
        return true;
    }

private:
    using PIUSI = pair<int, unordered_set<int> >;
};

