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


#include <climits>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <random>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>

using namespace std;

// 哈希表，自定义哈希函数
class Solution4 {
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
                ++mapping[cur_pair];
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

// 哈希表，自定义哈希函数
// duplicates 单独做
class Solution_3 {
public:
    int maxPoints(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n == 1 || n == 2) return n;
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            Point origin(points[i][0], points[i][1]);
            int result = 0;
            int duplicates = 1;
            unordered_map<PPP, int, MyHash, MyCmp> mapping;
            mapping.insert({{origin, origin}, 1});
            for(int j = i + 1; j < n; ++j)
            {
                Point cur(points[j][0], points[j][1]);
                if(cur == origin)
                    ++duplicates;
            }
            for(int j = i + 1; j < n; ++j)
            {
                Point cur(points[j][0], points[j][1]);
                if(cur == origin)
                    continue;
                PPP cur_pair({origin, cur});
                ++mapping[cur_pair];
                result = max(result, mapping[cur_pair]);
            }
            result += duplicates;
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
            return ((ll)hash<int>()(slope.first) * 10007 + hash<int>()(slope.second)) % MOD;
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
            return slope1 == slope2;
        }
    };
};

// 重载 == 实现比较规则
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

bool operator==(const PPP& point_pair1, const PPP& point_pair2)
{
    PII slope1 = point_pair1.second.get_slope(point_pair1.first);
    PII slope2 = point_pair2.second.get_slope(point_pair2.first);
    return slope1 == slope2;
}

class MyHash
{
public:
    int operator()(const PPP& point_pair) const
    {
        PII slope = point_pair.second.get_slope(point_pair.first);
        return ((ll)hash<int>()(slope.first) * 10007 + hash<int>()(slope.second)) % MOD;
    }
    const int MOD = 1e9 + 7;
    using ll = long long;
};

class Solution_4 {
public:
    int maxPoints(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n == 1 || n == 2) return n;
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            Point origin(points[i][0], points[i][1]);
            int result = 0;
            int duplicates = 1;
            unordered_map<PPP, int, MyHash> mapping;
            mapping.insert({{origin, origin}, 1});
            for(int j = i + 1; j < n; ++j)
            {
                Point cur(points[j][0], points[j][1]);
                if(cur == origin)
                    ++duplicates;
            }
            for(int j = i + 1; j < n; ++j)
            {
                Point cur(points[j][0], points[j][1]);
                if(cur == origin)
                    continue;
                PPP cur_pair({origin, cur});
                ++mapping[cur_pair];
                result = max(result, mapping[cur_pair]);
            }
            result += duplicates;
            ans = max(ans, result);
        }
        return ans;
    }
};


// RANSAC
// 在 STL 容器中随机选择
template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator *g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(*g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, &gen);
}

class Solution_2 {
public:
    int maxPoints(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        if(n == 1 || n == 2) return n;
        // 迭代最大次数，每次得到更好的估计会优化 iter_num 的数值
        int iter_num = INT_MAX;
        // 数据和模型之间可接受的差值
        const long double eps = 1e-10;
        // 最好模型的参数估计和内点数目
        int best_a = 0;
        int best_b = 0;
        int ans = 0;
        // 希望的得到正确模型的概率
        const double P = 0.9999;
        for(int i = 0; i < iter_num; ++i)
        {
            // 随机选两个点求解模型
            auto it1 = select_randomly(points.begin(), points.end());
            auto it2 = select_randomly(points.begin(), points.end());
            while(it1 - points.begin() == it2 - points.begin())
                it2 = select_randomly(points.begin(), points.end());
            int x1 = (*it1)[0];
            int y1 = (*it1)[1];
            int x2 = (*it2)[0];
            int y2 = (*it2)[1];

            // y = ax + b 求解出a，b
            long double a, b;
            if(x2 == x1)
            {
                a = (long double)INT_MAX;
                b = (long double)INT_MAX;
            }
            else if(y2 == y1)
            {
                a = 0.0;
                b = y2;
            }
            else
            {
                a = (long double)(y2 - y1) / (x2 - x1);
                b = y1 - a * x1;
            }

            // 算出内点数目
            int total_inlier = 0;
            for(int j = 0; j < n; ++j)
            {
                int x = points[j][0], y = points[j][1];
                long double y_estimate = 0.0;
                if(abs(a - (long double)INT_MAX) < eps)
                {
                    if(x == x1)
                        ++total_inlier;
                }
                else if(abs(a - 0.0) < eps)
                {
                    if(y == y1)
                        ++total_inlier;
                }
                else
                {
                    y_estimate = a * x + b;
                    if(abs(y_estimate - y) < eps)
                        ++total_inlier;
                }
            }

            // 判断当前的模型是否比之前估算的模型好
            if(total_inlier > ans)
            {
                best_a = a;
                best_b = b;
                ans = total_inlier;
                iter_num = log(1 - P) / log(1 - pow((double)total_inlier / n, 2));
            }

            if(total_inlier >= n) break;
        }
        return ans;
    }
};

//
class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n == 1)
            return 1;
        int max_cnt = 0;
        for(int i = 0; i < n - 1; ++i)
        {
            // 经过 points[i] 的直线
            // mapping[i][j] := 方向向量除以最大公约数后为 (i, j) 的点数, i >= 0
            map<int, map<int, int>> mapping;
            int duplicate = 1;
            for(int j = i + 1; j < n; ++j)
            {
                int a = points[i][0] - points[j][0];
                int b = points[i][1] - points[j][1];
                if(a == 0 && b == 0)
                {
                    ++duplicate;
                    continue;
                }
                if(a < 0)
                {
                    a = -a;
                    b = -b;
                }
                if(a != 0 && b != 0)
                {
                    int gcd_ = gcd<int>(abs(a), abs(b));
                    a /= gcd_;
                    b /= gcd_;
                }
                else if(b != 0)
                    b = INT_MAX / 2;
                else if(a != 0)
                    a = INT_MAX / 2;
                ++mapping[a][b];
            }
            max_cnt = max(max_cnt, duplicate);
            for(auto a: mapping)
                for(auto b: a.second)
                    max_cnt = max(max_cnt, b.second + duplicate);
        }
        return max_cnt;
    }
};

