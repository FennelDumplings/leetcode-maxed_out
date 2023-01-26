// prob587: Erect the Fence

/*
 * https://leetcode-cn.com/problems/erect-the-fence/
 */

#include <vector>
#include <algorithm>
#include <stack>
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

vector<Vector2> convex_hull(vector<Vector2>& p)
{
    int n = p.size();
    sort(p.begin(), p.end());
    vector<Vector2> result(n * 2);
    int k = 0; // 当前的凸包点个数，即 result.size()
    // 构造凸包的下侧
    for(int i = 0; i < n; ++i)
    {
        while(k > 1 && (result[k - 1] - result[k - 2]).cross(p[i] - result[k - 1]) < 0)
            --k;
        result[k++] = p[i];
    }
    // 构造凸包的上侧
    int t = k;
    for(int i = n - 2; i >= 0; --i)
    {
        while(k > t && (result[k - 1] - result[k - 2]).cross(p[i] - result[k - 1]) < 0)
            --k;
        result[k++] = p[i];
    }
    result.resize(k - 1);
    return result;
}

class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& points) {
        int n = points.size();
        if(n <= 3)
            return points;
        vector<Vector2> p;
        for(int i = 0; i < n; ++i)
            p.emplace_back(points[i][0], points[i][1]);
        bool flag = true;
        for(int i = 0; i < n; ++i)
        {
            int j = (i + 1) % n;
            int k = (i + 2) % n;
            if(fabs(ccw(p[i], p[j], p[k])) > EPS)
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            // 所有点共线
            return points;
        }
        vector<Vector2> ch = convex_hull(p);
        int m = ch.size();
        vector<vector<int>> result(m, vector<int>(2));
        for(int i = 0; i < m; ++i)
        {
            result[i][0] = ch[i].x;
            result[i][1] = ch[i].y;
        }
        return result;
    }
};
