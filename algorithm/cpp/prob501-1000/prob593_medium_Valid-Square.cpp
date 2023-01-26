// prob593: Valid Square

/*
 * https://leetcode-cn.com/problems/valid-square/
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


struct Cmp
{
    Vector2 O;
    Cmp(Vector2 p0)
    {
        O = p0;
    }
    bool operator()(const Vector2& p1, const Vector2& p2) const
    {
        return ccw(O, p1, p2) > 0;
    }
};

class Solution {
public:
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        vector<Vector2> points;
        points.emplace_back(p1[0], p1[1]);
        points.emplace_back(p2[0], p2[1]);
        points.emplace_back(p3[0], p3[1]);
        points.emplace_back(p4[0], p4[1]);
        Vector2 O(0, 0);
        for(Vector2 p: points)
        {
            O.x += p.x;
            O.y += p.y;
        }
        O.x /= 4;
        O.y /= 4;
        for(Vector2 p: points)
            if(fabs(p.x - O.x) < EPS && fabs(p.y - O.y) < EPS)
                return false;
        Cmp cmp(O);
        sort(points.begin(), points.end(), cmp);
        double c = (points[1] - points[0]).norm();
        for(int i = 0; i < 4; ++i)
        {
            cout << points[i].x << " " << points[i].y << endl;
            Vector2 a = points[(i + 1) % 4] - points[i];
            Vector2 b = points[(i - 1 + 4) % 4] - points[i];
            cout << a.x << " " << a.y << endl;
            cout << b.x << " " << b.y << endl;
            if(fabs(a.norm() - c) > EPS)
                return false;
            if(!a.perpendicular(b))
                return false;
        }
        return true;
    }
};
