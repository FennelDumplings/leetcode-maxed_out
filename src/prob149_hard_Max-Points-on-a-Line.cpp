// prob149: Max Points on a Line

/*
 * Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.
 */

/*
 * Example 1:
 * Input: [[1,1],[2,2],[3,3]]
 * Output: 3
 * Explanation:
 * ^
 * |
 * |        o
 * |     o
 * |  o  
 * +------------->
 * 0  1  2  3  4
 * Example 2:
 * Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
 * Output: 4
 * Explanation:
 * ^
 * |
 * |  o
 * |     o        o
 * |        o
 * |  o        o
 * +------------------->
 * 0  1  2  3  4  5  6
 */


#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// 哈希表，自定义哈希函数
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n == 1 || n == 2) return n;
        int ans = 1;
        unordered_map<PPP, int, MyHash, MyCmp> mapping;
        for(int i = 0; i < n; ++i)
        {
            Point origin(points[i][0], points[i][1]);
            int result = 0;
            if(mapping.find({origin, origin}) != mapping.end())
                continue;
            mapping.insert({{origin, origin}, 1});
            for(int j = i + 1; j < n; ++j)
            {
                Point cur(points[j][0], points[j][1]);
                PPP cur_pair({origin, cur});
                auto it = mapping.find(cur_pair);
                if(it == mapping.end())
                    mapping.insert({cur_pair, 1});
                else
                    ++(it -> second);
                if(cur != origin)
                    result = max(result, mapping[cur_pair]);
            }
            result += mapping[{origin, origin}];
            ans = max(ans, result);
        }
        return ans;
    }

private:
    using PII = pair<int, int>;
    class Point
    {
    public:
        Point(int x, int y): x(x), y(y) {}

        PII get_slope(const Point& origin) const
        {
            int dx = x - origin.x, dy = y - origin.y;
            if(dx == 0 && dy == 0) return PII({0, 0});
            if(dx == 0) return PII({0, 1});
            if(dy == 0) return PII({1, 0});
            if(dy < 0)
            {
                dy = -dy;
                dx = -dx;
            }
            int dx_sign = 1;
            if(dx < 0)
            {
                dx = -dx;
                dx_sign = -1;
            }
            int gcd = _gcd(dx, dy);
            dx /= gcd;
            dx *= dx_sign;
            dy /= gcd;
            return PII({dx, dy});
        }

        int get_x() const {return x;}
        int get_y() const {return y;}

        bool operator ==(const Point& point) const
        {
            return point.get_x() == x && point.get_y() == y;
        }

        bool operator !=(const Point& point) const
        {
            return !(*this == point);
        }

    private:
        int x, y;
        int _gcd(int x, int y) const
        {
            return x == 0 ? y : _gcd(y % x, x);
        }
    };

    using PPP = pair<Point, Point>;

    class MyHash
    {
    public:
        int operator()(const PPP& point_pair) const
        {
            PII slope = point_pair.second.get_slope(point_pair.first);
            return ((ll)point_pair.first.get_x() * 10007 + point_pair.first.get_y() +
                (ll)hash<int>()(slope.first) * 10007 + hash<int>()(slope.second)) % MOD;
        }
        const int MOD = 1e9 + 7;
        using ll = long long;
    };

    class MyCmp
    {
    public:
        bool operator()(const PPP& point_pair1, const PPP& point_pair2) const
        {
            PII slope1 = point_pair1.second.get_slope(point_pair1.first);
            PII slope2 = point_pair2.second.get_slope(point_pair2.first);
            return slope1 == slope2 && point_pair1.first == point_pair2.first;
        }
    };

};
