// prob1453: Maximum Number of Darts Inside of a Circular Dartboard

/*
 * https://leetcode-cn.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/
 */

#include <cmath>
#include <algorithm>
#include <vector>

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

// 返回点 P 以点 O 为圆心逆时针旋转 alpha 后所在的位置
Vector2 rotate(Vector2 O, double alpha, Vector2 P)
{
    Vector2 new_P;
    Vector2 OP = P - O;
    new_P.x = OP.x * cos(alpha) - OP.y * sin(alpha) + O.x;
    new_P.y = OP.y * cos(alpha) + OP.x * sin(alpha) + O.y;
    return new_P;
}

Vector2 get_center(Vector2 P1, Vector2 P2, double r)
{
    Vector2 P1P2 = (P2 - P1);
    Vector2 P_mid = P1 + P1P2 * 0.5;
    double d = sqrt((r * r) - (P1P2.norm() * P1P2.norm() * 0.25));
    Vector2 O = P_mid + rotate(Vector2(0, 0), PI * 0.5, P1P2.normalize()) * d;
    return O;
}

class Solution_2 {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        vector<Vector2> p;
        int n = points.size();
        for(int i = 0; i < n; ++i)
            p.emplace_back(points[i][0], points[i][1]);
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            Vector2 P1 = p[i];
            for(int j = 0; j < n; ++j)
            {
                if(i == j) continue;
                Vector2 P2 = p[j];
                if((P2 - P1).norm() < EPS)
                    continue;
                if((P2 - P1).norm() > r * 2.0)
                    continue;
                Vector2 O = get_center(P1, P2, r);
                int cnt = 0;
                for(int k = 0; k < n; ++k)
                {
                    if(k == i || k == j)
                        continue;
                    Vector2 P = p[k];
                    if((P - O).norm() - r < EPS)
                        ++cnt;
                }
                ans = max(ans, cnt + 2);
            }
        }
        return ans;
    }
};


// 扫描线
struct Event
{
    double theta; // 角度 [0, 2PI)
    int ori; // 0 为进入，1 为离开
    Event(double theta, int ori):theta(theta),ori(ori){}
    bool operator<(const Event& e) const
    {
        if(fabs(theta - e.theta) < EPS)
            return ori < e.ori;
        return theta < e.theta;
    }
};

class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        int n = points.size();
        vector<vector<double>> d(n, vector<double>(n));
        vector<Vector2> p(n);
        for(int i = 0; i < n; ++i)
        {
            p[i].x = points[i][0];
            p[i].y = points[i][1];
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                d[i][j] = (p[i] - p[j]).norm();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            const Vector2& P = p[i];
            vector<Event> events;
            for(int j = 0; j < n; ++j)
            {
                if(i == j) continue;
                if(d[i][j] > r * 2)
                    continue;
                const Vector2& Q = p[j];
                // double A = (Q - P).polar();
                double A = atan((P.y - Q.y) / (P.x - Q.x));
                double B = acos(d[i][j] / (r * 2));
                double alpha = A - B;
                double beta = A + B;
                events.emplace_back(alpha, 0);
                events.emplace_back(beta, 1);
            }
            sort(events.begin(), events.end());
            int m = events.size();
            int cnt = 0;
            int max_cnt = 0;
            for(int j = 0; j < m; ++j)
            {
                if(events[j].ori == 0)
                    ++cnt;
                else
                    --cnt;
                max_cnt = max(max_cnt, cnt);
            }
            ans = max(ans, max_cnt + 1);
        }
        return ans;
    }
};
