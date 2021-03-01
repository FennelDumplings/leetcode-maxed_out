// interview16.13: 平分正方形

/*
 * https://leetcode-cn.com/problems/bisect-squares-lcci/
 */

#include <vector>
#include <cmath>
#include <algorithm>

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

// 判断交点是否落在线段上
bool inBoundingRectangle(Vector2 x, Vector2 a, Vector2 b)
{
    // x, a, b 同线
    // 判断 x 是否在包含 (a, b) 且各边平行于 x 轴，y 轴的最小四边形内部。
    if(b < a) swap(a, b);
    return x == a || x == b || (a < x && x < b);
}

class Solution {
public:
    vector<double> cutSquares(vector<int>& square1, vector<int>& square2) {
        Vector2 A1(square1[0], square1[1]), A2(square1[0] + square1[2], square1[1] + square1[2]);
        Vector2 B1(square2[0], square2[1]), B2(square2[0] + square2[2], square2[1] + square2[2]);
        Vector2 O1 = (A1 + A2) * 0.5;
        Vector2 O2 = (B1 + B2) * 0.5;
        if(O1 == O2)
        {
            return {O1.x, min(A1.y, B1.y), O1.x, max(A2.y, B2.y)};
        }
        Vector2 A3(square1[0], square1[1] + square1[2]), A4(square1[0] + square1[2], square1[1]);
        Vector2 B3(square2[0], square2[1] + square2[2]), B4(square2[0] + square2[2], square2[1]);
        vector<Vector2> A{A1, A3, A2, A4};
        vector<Vector2> B{B1, B3, B2, B4};
        vector<Vector2> cand;
        traverse_edge(A, cand, O1, O2);
        traverse_edge(B, cand, O1, O2);
        sort(cand.begin(), cand.end());
        return {cand.front().x, cand.front().y, cand.back().x, cand.back().y};
    }

private:
    void traverse_edge(const vector<Vector2>& A, vector<Vector2>& cand, const Vector2& O1, const Vector2& O2)
    {
        for(int i = 0; i < 4; ++i)
        {
            Vector2 p1 = A[i], p2 = A[(i + 1) % 4];
            Vector2 X;
            if(lineIntersection(p1, p2, O1, O2, X))
            {
                if(inBoundingRectangle(X, p1, p2))
                {
                    cand.push_back(X);
                }
            }
        }
    }
};
