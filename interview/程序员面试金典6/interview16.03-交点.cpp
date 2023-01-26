// interview16.03: Intersection LCCI

/*
 * https://leetcode-cn.com/problems/intersection-lcci/
 */

#include <cmath>
#include <vector>

using namespace std;

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
        if(abs(x - vec.x) < EPS)
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
        return dot(vec) < EPS;
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


// 直线与直线相交
bool lineIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x)
{
    // 平行或重叠返回 false
    // (b - a) 是 (a, b) 的方向向量
    // (d - c) 是 (c, d) 的方向向量
    double det = (b - a).cross(d - c);
    if(fabs(det) < EPS)
        return false;
    x = a + (b - a) * ((c - a).cross(d - c) / det);
    return true;
}

// 线段与线段相交
bool parallelSegments(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x)
{
    // (a, b) , (c, d) 平行时，判断是否相接与一点
    if(b < a) swap(a, b);
    if(d < c) swap(c, d);
    // 两条线段不在同一条直线以及两条线段不重叠的情况
    if(ccw(a, b, c) != 0 || b < c || d < a) return false;
    if(a < c)
        x = c;
    else
        x = a;
    return true;
}
bool inBoundingRectangle(Vector2 x, Vector2 a, Vector2 b)
{
    // x, a, b 同线
    // 判断 x 是否在包含 (a, b) 且各边平行于 x 轴，y 轴的最小四边形内部。
    if(b < a) swap(a, b);
    return x == a || x == b || (a < x && x < b);
}
bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d, Vector2& x)
{
    // 将 (a, b) , (c, d) 的交点返回 x
    // 多个交点返回任交点
    // 不相交返回 false
    if(!lineIntersection(a, b, c, d, x))
    {
        // 两条线段平行
        return parallelSegments(a, b, c, d, x);
    }
    // 两条直线有交点 x
    // 仅当两条线段都包含 x 时返回真
    return inBoundingRectangle(x, a, b) && inBoundingRectangle(x, c, d);
}

class Solution {
public:
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        Vector2 a(start1[0], start1[1]);
        Vector2 b(end1[0], end1[1]);
        Vector2 c(start2[0], start2[1]);
        Vector2 d(end2[0], end2[1]);
        Vector2 x(0, 0);
        bool flag = segmentIntersection(a, b, c, d, x);
        if(!flag)
            return {};
        return {x.x, x.y};
    }
};
