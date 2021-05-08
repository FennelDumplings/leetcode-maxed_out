// prob836: Rectangle Overlap

/*
 * A rectangle is represented as a list [x1, y1, x2, y2], where (x1, y1) are the coordinates of its bottom-left corner, and (x2, y2) are the coordinates of its top-right corner.
 * Two rectangles overlap if the area of their intersection is positive.  To be clear, two rectangles that only touch at the corner or edges do not overlap.
 * Given two (axis-aligned) rectangles, return whether they overlap.
 */

/*
 * Example 1:
 * Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]
 * Output: true
 * Example 2:
 * Input: rec1 = [0,0,1,1], rec2 = [1,0,2,1]
 * Output: false
 */

/*
 * Notes:
 * Both rectangles rec1 and rec2 are lists of 4 integers.
 * All coordinates in rectangles will be between -10^9 and 10^9.
 */

#include <vector>
#include <cmath>
#include <set>

using namespace std;

// 直接分类讨论
class Solution_2 {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        // x1, y1, x2, y2
        return !((rec2[2] <= rec1[0]) || (rec1[2] <= rec2[0])
            || (rec1[3] <= rec2[1]) || (rec2[3] <= rec1[1]));
    }
};

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

// 仅判断两条线段是否相交，不需要交点
bool segmentIntersection(Vector2 a, Vector2 b, Vector2 c, Vector2 d)
{
    double ab = ccw(a, b, c) * ccw(a, b, d);
    double cd = ccw(c, d, a) * ccw(c, d, b);
    // 两条线段在同一直线上或者端点相互重叠，不算相交
    if(fabs(ab) < EPS || fabs(cd) < EPS)
        return false;
    return ab < 0 && cd < 0;
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

// 判定对多边形 p 和 q 是否相交(相连或重叠)
// 只有一个点的重叠也是重叠
bool polygonIntersects(const vector<Vector2>& p, const vector<Vector2>& q)
{
    int n = p.size(), m = q.size();
    // 一个多边形的点在另一个多边形的内部
    if(isInside(p, q[0]) || isInside(q, p[0]))
        return true;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j)
        {
            if(segmentIntersection(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
                return true;
        }
    return false;
}

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        vector<Vector2> p, q;
        p.emplace_back(rec1[0], rec1[1]);
        p.emplace_back(rec1[0], rec1[3]);
        p.emplace_back(rec1[2], rec1[3]);
        p.emplace_back(rec1[2], rec1[1]);
        q.emplace_back(rec2[0], rec2[1]);
        q.emplace_back(rec2[0], rec2[3]);
        q.emplace_back(rec2[2], rec2[3]);
        q.emplace_back(rec2[2], rec2[1]);
        int n = p.size(), m = q.size();
        // 矩形退化成直线的情况
        for(int i = 0; i < n; ++i)
        {
            if(fabs((p[(i + 1) % 4] - p[i]).norm()) < EPS)
                return false;
        }
        for(int j = 0; j < m; ++j)
        {
            if(fabs((q[(j + 1) % 4] - q[j]).norm()) < EPS)
                return false;
        }
        return polygonIntersects(p, q);
    }
};
