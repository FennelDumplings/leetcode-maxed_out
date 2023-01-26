// prob963: Minimum Area Rectangle II

/*
 * https://leetcode-cn.com/problems/minimum-area-rectangle-ii/
 */

#include <unordered_set>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

// 二维向量
const double PI = 2.0 * acos(0.0);
const double EPS = 1e-10;

struct Vector2
{
    double x, y;
    // 把构造函数指定 explicit，可以放置发生在 Vector2 的位置中加入实数的错误
    explicit Vector2(double x_=0, double y_=0):x(x_),y(y_){}

    // 比较两个向量
    bool operator==(const Vector2& vec) const
    {
        return fabs(x - vec.x) < EPS && fabs(y - vec.y) < EPS;
    }
    bool operator<(const Vector2& vec) const
    {
        if(fabs(x - vec.x) < EPS)
            return y < vec.y;
        return x < vec.x;
    }

    // 向量的加法和减法
    Vector2 operator+(const Vector2& vec) const
    {
        return Vector2(x + vec.x, y + vec.y);
    }
    Vector2 operator-(const Vector2& vec) const
    {
        return Vector2(x - vec.x, y - vec.y);
    }

    // 向量的数乘
    Vector2 operator*(double a) const
    {
        return Vector2(x * a, y * a);
    }

    // 向量的模
    double norm() const
    {
        return hypot(x, y);
    }

    // 返回方向相同的单位向量
    // 零向量不可调用
    Vector2 normalize() const
    {
        return Vector2(x / norm(), y / norm());
    }

    // 从 x 轴正方向转到当前向量的角度
    double polar() const
    {
        // atan2 返回 (-PI, PI]，修正为 [0，2PI)
        // fmod 求两个实数相除的余数
        return fmod(atan2(y, x) + 2 * PI, 2 * PI);
    }

    // 内积
    double dot(const Vector2& vec) const
    {
        return x * vec.x + y * vec.y;
    }
    double cross(const Vector2& vec) const
    {
        return x * vec.y - y * vec.x;
    }

    // 当前向量映射到另一向量的结果
    // vec的长度需要大于0
    Vector2 project(const Vector2& vec) const
    {
        Vector2 r = vec.normalize();
        return r * r.dot(*this);
    }

    // 两个向量的夹角
    // 两个向量长度均需要大于 0
    double insersection_angle(const Vector2& vec) const
    {
        return acos(dot(vec) / norm() * vec.norm());
    }

    // 判断两个向量是否垂直
    // 两个向量长度均需要大于 0
    bool perpendicular(const Vector2& vec) const
    {
        return fabs(dot(vec)) < EPS;
    }

    // 平行四边形面积
    double parallelogram_area(const Vector2& vec) const
    {
        return fabs(cross(vec));
    }

    // 三角形面积，可以扩找到多边形
    double triangle_area(const Vector2& vec) const
    {
        return fabs(cross(vec)) / 2;
    }
};

// 判定两个向量的方向
// ccw: counter clock wise
double ccw(const Vector2& a, const Vector2& b)
{
    // 正数: b 在 a 的逆时针 180 度内
    // 负数: b 在 a 的顺时针 180 度内
    // 0: 平行
    return a.cross(b);
}
double ccw(const Vector2& p, const Vector2& a, const Vector2& b)
{
    // 正数: 以 p 为基准点时，b 在 a 的逆时针 180 度内
    // 负数: 以 p 为基准点时，b 在 a 的顺时针 180 度内
    return ccw(a - p, b - p);
}


class Solution2 {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        using ll = long long;
        int n = points.size();
        ll base = 4e4 + 5;
        unordered_set<ll> setting;
        for(int i = 0; i < n; ++i)
            setting.insert(points[i][0] * base + points[i][1]);
        double ans = INT_MAX;
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j)
            {
                int x1 = points[i][0], y1 = points[i][1];
                int x2 = points[j][0], y2 = points[j][1];
                Vector2 p1(x1, y1), p2(x2, y2);
                // p1, p2 是对角线
                for(int k = 0; k < n; ++k)
                {
                    if(k == i || k == j)
                        continue;
                    int x3 = points[k][0], y3 = points[k][1];
                    Vector2 p3(x3, y3);
                    int x4 = x1 + x2 - x3, y4 = y1 + y2 - y3;
                    if(setting.count(x4 * base + y4) > 0)
                        if(fabs((p1 - p3).dot(p2 - p3)) < EPS)
                            ans = min(ans, (p1 - p3).norm() * (p2 - p3).norm());
                }
            }
        if(fabs(ans - INT_MAX) < EPS)
            return 0;
        return ans;
    }
};

#include <unordered_map>

// long double 作键
using LD = long double;
LD base = 4e4 + 7;

struct Info
{
    Vector2 mid;
    LD len;
    Info(Vector2 p, LD len):mid(p),len(len){}
};

struct MyCmp
{
    bool operator()(const Info& info1, const Info& info2) const
    {
        return (info1.mid == info2.mid && fabs(info1.len - info2.len) < EPS);
    }
};

struct MyHash
{
    bool operator()(const Info& info) const
    {
        return info.len * base * base + info.mid.x * base + info.mid.y;
    }
};

class Solution3 {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        vector<Vector2> ps(n);
        for(int i = 0; i < n; ++i)
        {
            ps[i].x = points[i][0];
            ps[i].y = points[i][1];
        }
        unordered_map<Info, vector<Vector2>, MyHash, MyCmp> mapping;
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j)
            {
                Vector2 p1 = ps[i], p2 = ps[j];
                Vector2 mid = (p1 + p2) * 0.5;
                LD len = (p1 - p2).norm();
                Info info(mid, len);
                mapping[info].push_back(p1);
            }
        double ans = INT_MAX;
        auto it = mapping.begin();
        while(it != mapping.end())
        {
            if((it -> second).size() == 1)
            {
                ++it;
                continue;
            }
            int m = (it -> second).size();
            for(int i = 0; i < m - 1; ++i)
            {
                Vector2 p1 = (it -> second)[i];
                for(int j = i + 1; j < m; ++j)
                {
                    Vector2 p2 = (it -> second)[j];
                    if(fabs((p2 - (it -> first).mid).cross(p1 - (it -> first).mid)) < EPS)
                        continue;
                    double delta_x = (it -> first).mid.x - p1.x;
                    double delta_y = (it -> first).mid.y - p1.y;
                    Vector2 p3(p1.x + delta_x * 2, p1.y + delta_y * 2);
                    ans = min(ans, (p2 - p1).norm() * (p2 - p3).norm());
                }
            }
            ++it;
        }
        if(fabs(ans - INT_MAX) < EPS)
            return 0;
        return ans;
    }
};

// 用多层 TreeMap
#include <map>

class Solution {
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        vector<Vector2> ps(n);
        for(int i = 0; i < n; ++i)
        {
            ps[i].x = points[i][0];
            ps[i].y = points[i][1];
        }
        map<double, map<Vector2, vector<Vector2>>> mapping;
        for(int i = 0; i < n - 1; ++i)
            for(int j = i + 1; j < n; ++j)
            {
                Vector2 p1 = ps[i], p2 = ps[j];
                Vector2 mid = (p1 + p2) * 0.5;
                double len = (p1 - p2).norm();
                mapping[len][mid].push_back(p1);
            }
        double ans = INT_MAX;
        auto it_len = mapping.begin();
        while(it_len != mapping.end())
        {
            double len = it_len -> first;
            const auto &sub_mapping = mapping[len];
            ++it_len;
            auto it_mid = sub_mapping.begin();
            while(it_mid != sub_mapping.end())
            {
                const Vector2 &mid = it_mid -> first;
                const vector<Vector2> &cand = it_mid -> second;
                ++it_mid;
                int m = cand.size();
                if(m == 1)
                    continue;
                for(int i = 0; i < m - 1; ++i)
                {
                    Vector2 p1 = cand[i];
                    for(int j = i + 1; j < m; ++j)
                    {
                        Vector2 p2 = cand[j];
                        if(fabs((p2 - mid).cross(p1 - mid)) < EPS)
                            continue;
                        double delta_x = mid.x - p1.x;
                        double delta_y = mid.y - p1.y;
                        Vector2 p3(p1.x + delta_x * 2, p1.y + delta_y * 2);
                        ans = min(ans, (p2 - p1).norm() * (p2 - p3).norm());
                    }
                }
            }
        }
        if(fabs(ans - INT_MAX) < EPS)
            return 0;
        return ans;
    }
};
