// prob1401: Circle and Rectangle Overlapping

/*
 * https://leetcode-cn.com/problems/circle-and-rectangle-overlapping/
 */

#include <vector>
#include <cmath>

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


// 判断交点是否落在线段上
bool inBoundingRectangle(Vector2 x, Vector2 a, Vector2 b)
{
    // x, a, b 同线
    // 判断 x 是否在包含 (a, b) 且各边平行于 x 轴，y 轴的最小四边形内部。
    if(b < a) swap(a, b);
    return x == a || x == b || (a < x && x < b);
}

// 点和线的距离
Vector2 perpendicularFoot(Vector2 p, Vector2 a, Vector2 b)
{
    // p 到 (a, b) 的垂足
    return a + (p - a).project(b - a);
}
double pointToTlineSeg(Vector2 p, Vector2 a, Vector2 b)
{
    // p 到直线 (a, b) 的距离
    Vector2 foot = perpendicularFoot(p, a, b);
    if(inBoundingRectangle(foot, a, b)) // 垂足在线段上
        return (p - foot).norm();
    return min((p - a).norm(), (p - b).norm());
}

// 点 q 是否包含在多边形 p 内部
// q 在多边形边上没有处理
bool isInside(const vector<Vector2>& p, Vector2 q)
{
    int crosses = 0;
    int n = p.size();
    for(int i = 0; i < n; ++i)
    {
        int j = (i + 1) % n;
        // p[i], p[j] 能否纵向分割射线
        if((p[i].y > q.y) != (p[j].y > q.y))
        {
            // 交点的横坐标
            double X = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
            if(q.x < X)
                ++crosses;
        }
    }
    return crosses % 2 == 1;
}

class Solution {
public:
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
        vector<Vector2> p;
        p.emplace_back(x1, y1);
        p.emplace_back(x2, y1);
        p.emplace_back(x2, y2);
        p.emplace_back(x1, y2);
        Vector2 O(x_center, y_center);
        if(isInside(p, O))
            return true;
        for(int i = 0; i < 4; ++i)
        {
            int j = (i + 1) % 4;
            double d = pointToTlineSeg(O, p[i], p[j]);
            if(d < radius || fabs(d - radius) < EPS)
                return true;
        }
        return false;
    }
};
