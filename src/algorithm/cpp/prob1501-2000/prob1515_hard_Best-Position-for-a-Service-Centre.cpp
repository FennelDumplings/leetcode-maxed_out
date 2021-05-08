// prob1515: Best Position for a Service Centre

/*
 * https://leetcode-cn.com/problems/best-position-for-a-service-centre/
 */

#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

// 二维向量
const double PI = 2.0 * acos(0.0);
const double EPS = 1e-7;

struct Vector2
{
    double x, y;
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

/*
struct Function
{
    // 二元函数
    vector<Vector2> points;
    Function(vector<vector<int>>& p)
    {
        int n = p.size();
        points = vector<Vector2>(n);
        for(int i = 0; i < n; ++i)
        {
            points[i].y = p[i][1];
            points[i].x = p[i][0];
        }
    }
    double operator()(double x, double y) const
    {
        double ans = 0;
        Vector2 p0(x, y);
        for(const Vector2 &p: points)
            ans += (p0 - p).norm();
        return ans;
    }
};

struct PartialFunction
{
    Function f; // 二元函数
    double x;
    PartialFunction(Function& f, double x):f(f),x(x){}
    double operator()(double y) const
    {
        return f(x, y);
    }
};

double ternary_search(PartialFunction& f, double L, double R)
{
    double l = L, r = R;
    while(l + EPS < r)
    {
        double m1 = l + (r - l) / 2.0;
        double m2 = m1 + (r - m1) / 2.0;
        if(f(m1) < f(m2))
            r = m2;
        else
            l = m1;
    }
    return l;
}

double ternary_search(Function& f, double Lx, double Rx, double Ly, double Ry)
{
    double lx = Lx, rx = Rx, ly = Ly, ry = Ry;
    double y_max = 0.0;
    while(lx + EPS < rx)
    {
        double xm1 = lx + (rx - lx) / 2.0;
        PartialFunction f1(f, xm1);
        double ym1_max = ternary_search(f1, ly, ry);
        double xm2 = xm1 + (rx - xm1) / 2.0;
        PartialFunction f2(f, xm2);
        double ym2_max = ternary_search(f2, ly, ry);
        if(f(xm1, ym1_max) < f(xm2, ym2_max))
        {
            y_max = ym1_max;
            rx = xm2;
        }
        else
        {
            y_max = ym2_max;
            lx = xm1;
        }
    }
    return f(lx, y_max);
}

class Solution_2 {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        Function f(positions);
        int Lx = positions[0][0], Rx = positions[0][0];
        int Ly = positions[0][1], Ry = positions[0][1];
        for(vector<int>& p: positions)
        {
            Lx = min(Lx, p[0]);
            Rx = max(Rx, p[0]);
            Ly = min(Ly, p[1]);
            Ry = max(Ry, p[1]);
        }
        if(Lx == Rx && Ly == Ry)
            return 0.0;
        if(Lx == Rx)
        {
            PartialFunction pf(f, Lx);
            return ternary_search(pf, Ly, Ry);
        }
        return ternary_search(f, Lx, Rx, Ly, Ry);
    }
};
*/

/*
struct Function
{
    // 二元函数
    vector<Vector2> *points;
    Function(vector<Vector2>* p):points(p){}
    double operator()(Vector2& p0) const
    {
        double ans = 0;
        for(Vector2 p: *points)
            ans += (p0 - p).norm();
        return ans;
    }
};

struct Gradient
{
    // 二元函数的梯度
    vector<Vector2> *points;
    Gradient(vector<Vector2>* p):points(p){}
    Vector2 operator()(const Vector2& p0, vector<int>& batch_data_idx) const
    {
        Vector2 nabla;
        for(int idx: batch_data_idx)
        {
            Vector2 p = (*points)[idx];
            nabla.x += (p0.x - p.x) / ((p0 - p).norm() + EPS);
            nabla.y += (p0.y - p.y) / ((p0 - p).norm() + EPS);
        }
        return nabla;
    }
};

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        Vector2 vec; // 初始值
        vector<Vector2> data; // 训练数据
        for(vector<int>& p: positions)
        {
            vec.x += p[0];
            vec.y += p[1];
            data.emplace_back(p[0], p[1]);
        }
        Gradient grad(&data);
        Function f(&data);
        vec = vec * (1 / (double)n);
        double gamma = 1.0; // 学习率
        double decay = 1e-3; // 学习率衰减
        int batch_size = 16;
        std::default_random_engine dre(6);
        vector<int> data_idx(n);
        for(int i = 0; i < n; ++i)
            data_idx[i] = i;
        Vector2 iter_vec = vec;
        vector<int> batch_data_idx;
        while(true)
        {
            shuffle(data_idx.begin(), data_idx.end(), dre);
            for(int i = 0; i < n; i += batch_size)
            {
                int j = min(i + batch_size, n);
                batch_data_idx.assign(j - i, 0);
                for(int k = i; k < j; ++k)
                    batch_data_idx[k - i] = data_idx[k];
                Vector2 g = grad(iter_vec, batch_data_idx);
                iter_vec = iter_vec - g * gamma; // 更新
                gamma *= (1.0 - decay); // 每一轮学习率衰减 1 次
            }
            if(vec == iter_vec)
                break;
            vec = iter_vec;
        }
        return f(vec);
    }
};
*/


struct Function
{
    // 二元函数
    vector<Vector2> *points;
    Function(vector<Vector2>* p):points(p){}
    double operator()(Vector2& p0) const
    {
        double ans = 0;
        for(Vector2 p: *points)
            ans += (p0 - p).norm();
        return ans;
    }
};

/*
class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        Vector2 vec; // 初始值
        vector<Vector2> data; // 训练数据
        for(vector<int>& p: positions)
        {
            vec.x += p[0];
            vec.y += p[1];
            data.emplace_back(p[0], p[1]);
        }
        Function f(&data);
        vec = vec * (1 / (double)n);
        double step = 1.0; // 步长
        double decay = 5e-1; // 步长衰减
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        Vector2 nxt_vec;
        while(step > EPS)
        {
            bool flag = false;
            for(int d = 0; d < 4; ++d)
            {
                nxt_vec.x = vec.x + step * dx[d];
                nxt_vec.y = vec.y + step * dy[d];
                if(f(nxt_vec) < f(vec))
                {
                    vec = nxt_vec;
                    flag = true;
                    break;
                }
            }
            if(!flag)
                step *= (1 - decay);
        }
        return f(vec);
    }
};
*/

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        int n = positions.size();
        Vector2 vec; // 初始值
        vector<Vector2> data; // 训练数据
        for(vector<int>& p: positions)
        {
            vec.x += p[0];
            vec.y += p[1];
            data.emplace_back(p[0], p[1]);
        }
        Function f(&data);
        vec = vec * (1 / (double)n);
        double step = 1.0; // 步长
        double decay = 5e-1; // 步长衰减
        double T0 = 5e-1;
        double min_T = 1e-8;
        double T_decay = 0.9; // 温度衰减
        double T = T0;
        int C = 10; // 每个温度的迭代次数
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        Vector2 nxt_vec;
        std::default_random_engine dre;
        std::uniform_real_distribution<double> dr;
        int c = 0;
        while(T > min_T)
        {
            bool flag = false;
            for(int d = 0; d < 4; ++d)
            {
                nxt_vec.x = vec.x + step * dx[d];
                nxt_vec.y = vec.y + step * dy[d];
                double delta = f(nxt_vec) - f(vec);
                if(delta < -EPS)
                {
                    vec = nxt_vec;
                    flag = true;
                    break;
                }
                else
                {
                    double r = dr(dre);
                    if(r < exp(-fabs(delta) / T))
                    {
                        vec = nxt_vec;
                        flag = true;
                        break;
                    }
                }
            }
            if(!flag && step > EPS)
                step *= (1 - decay);
            if(++c == C)
            {
                c = 0;
                T = T * T_decay;
            }
        }
        return f(vec);
    }
};
