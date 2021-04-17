
#include <vector>
#include <cmath>
#include <map>
#include <set>

using namespace std;

// 二维向量
const double PI = 2.0 * acos(0.0);
const double EPS = 1e-10;

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

struct Line
{
    // line: a+pb, a 是点, b 是方向向量
    Vector2 a;
    Vector2 b;
    double deg; // 极角
    Line(Vector2 a, Vector2 b):a(a),b(b)
    {
        deg = b.polar();
    }
    bool operator<(const Line& l) const
    {
        // 方向向量的极角序
        return deg < l.deg;
    }
};

// 直线与直线相交
bool line_intersection(const Line& l1, const Line& l2, Vector2& x)
{
    double det = l1.b.cross(l2.b); // 两个方向向量的外积
    // 平行或重叠返回false
    if(fabs(det) < EPS)
        return false;
    // 两条有向直线的交点
    Vector2 u = l1.a - l2.a;
    double t = l2.b.cross(u) / det;
    x = l1.a + l1.b * t;
    return true;
}

class Solution {
public:
    double minRecSize(vector<vector<int>>& lines_) {
        int n = lines_.size();
        if(n <= 2)
            return 0;
        // 按斜率分桶，并用 map 维护升序，桶内是从小到大的截距
        map<int, set<int>> mapping;
        for(const vector<int>& l: lines_)
            mapping[l[0]].insert(l[1]);
        // 每个斜率取最大和最小的截距构造线段，并按 map 中的顺序(也就是斜率从小到大的顺序)保存在 vector 中
        vector<vector<Line>> lines;
        auto it = mapping.begin();
        while(it != mapping.end())
        {
            // 遇到了新的斜率，需要新分配该斜率的桶
            lines.push_back({});
            Vector2 b(1, it -> first); // 方向向量
            Vector2 a(0, *(it -> second).begin()); // 截距点
            lines.back().emplace_back(a, b);
            if((it -> second).size() > 1)
            {
                Vector2 b2(1, it -> first); // 方向向量
                Vector2 a2(0, *(it -> second).rbegin()); // 截距点
                lines.back().emplace_back(a2, b2);
            }
            ++it;
        }
        if(lines.size() < 2) // 所有直线只有一种斜率不会有交点
            return 0;

        vector<Vector2> points; // 在桶中所有相邻斜率的直线形成的交点
        for(int i = 0; i < (int)lines.size(); ++i)
        {
            int j = (i + 1) % (int)lines.size();
            // lines[i] 为当前斜率对应的一条或两条需要考虑的直线
            // lines[j] 为相邻的下一个斜率对应的一条或两条需要考虑的直线
            for(Line l1: lines[i])
                for(Line l2: lines[j])
                {
                    Vector2 x(-1e9, -1e9);
                    if(line_intersection(l1, l2, x))
                        points.push_back(x);
                }
        }

        // 统计答案
        double min_x = points[0].x;
        double min_y = points[0].y;
        double max_x = points[0].x;
        double max_y = points[0].y;
        for(Vector2 p: points)
        {
            min_x = min(min_x, p.x);
            min_y = min(min_y, p.y);
            max_x = max(max_x, p.x);
            max_y = max(max_y, p.y);
        }
        if(abs(max_x - min_x) < EPS)
            return 0;
        if(abs(max_y - min_y) < EPS)
            return 0;
        double ans = abs(max_x - min_x) * abs(max_y - min_y);
        return ans;
    }
};
