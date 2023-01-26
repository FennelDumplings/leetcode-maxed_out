// interview16.03: 交点

/*
 * https://leetcode-cn.com/problems/intersection-lcci/
 */

#include <vector>

using namespace std;

// 以下均为别人的代码

// 参数方程
class Solution {
public:
    // 判断 (xk, yk) 是否在「线段」(x1, y1)~(x2, y2) 上
    // 这里的前提是 (xk, yk) 一定在「直线」(x1, y1)~(x2, y2) 上
    bool inside(int x1, int y1, int x2, int y2, int xk, int yk) {
        // 若与 x 轴平行，只需要判断 x 的部分
        // 若与 y 轴平行，只需要判断 y 的部分
        // 若为普通线段，则都要判断
        return (x1 == x2 || (min(x1, x2) <= xk && xk <= max(x1, x2))) && (y1 == y2 || (min(y1, y2) <= yk && yk <= max(y1, y2)));
    }

    void update(vector<double>& ans, double xk, double yk) {
        // 将一个交点与当前 ans 中的结果进行比较
        // 若更优则替换
        if (!ans.size() || xk < ans[0] || (xk == ans[0] && yk < ans[1])) {
            ans = {xk, yk};
        }
    }

    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        int x1 = start1[0], y1 = start1[1];
        int x2 = end1[0], y2 = end1[1];
        int x3 = start2[0], y3 = start2[1];
        int x4 = end2[0], y4 = end2[1];

        vector<double> ans;
        // 判断 (x1, y1)~(x2, y2) 和 (x3, y3)~(x4, y3) 是否平行
        if ((y4 - y3) * (x2 - x1) == (y2 - y1) * (x4 - x3)) {
            // 若平行，则判断 (x3, y3) 是否在「直线」(x1, y1)~(x2, y2) 上
            if ((y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)) {
                // 判断 (x3, y3) 是否在「线段」(x1, y1)~(x2, y2) 上
                if (inside(x1, y1, x2, y2, x3, y3)) {
                    update(ans, (double)x3, (double)y3);
                }
                // 判断 (x4, y4) 是否在「线段」(x1, y1)~(x2, y2) 上
                if (inside(x1, y1, x2, y2, x4, y4)) {
                    update(ans, (double)x4, (double)y4);
                }
                // 判断 (x1, y1) 是否在「线段」(x3, y3)~(x4, y4) 上
                if (inside(x3, y3, x4, y4, x1, y1)) {
                    update(ans, (double)x1, (double)y1);
                }
                // 判断 (x2, y2) 是否在「线段」(x3, y3)~(x4, y4) 上
                if (inside(x3, y3, x4, y4, x2, y2)) {
                    update(ans, (double)x2, (double)y2);
                }
            }
            // 在平行时，其余的所有情况都不会有交点
        }
        else {
            // 联立方程得到 t1 和 t2 的值
            double t1 = (double)(x3 * (y4 - y3) + y1 * (x4 - x3) - y3 * (x4 - x3) - x1 * (y4 - y3)) / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
            double t2 = (double)(x1 * (y2 - y1) + y3 * (x2 - x1) - y1 * (x2 - x1) - x3 * (y2 - y1)) / ((x4 - x3) * (y2 - y1) - (x2 - x1) * (y4 - y3));
            // 判断 t1 和 t2 是否均在 [0, 1] 之间
            if (t1 >= 0.0 && t1 <= 1.0 && t2 >= 0.0 && t2 <= 1.0) {
                ans = {x1 + t1 * (x2 - x1), y1 + t1 * (y2 - y1)};
            }
        }
        return ans;
    }
};


// 向量
// 叉积
class Solution {
public:
    using Coor = vector <double>;
    static constexpr double EPS = 1E-6;

    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        int ax = start1[0], ay = start1[1], bx = end1[0], by = end1[1];
        int cx = start2[0], cy = start2[1], dx = end2[0], dy = end2[1];
        int acx = cx - ax, acy = cy - ay, abx = bx - ax, aby = by - ay, adx = dx - ax, ady = dy - ay;
        int cax = ax - cx, cay = ay - cy, cbx = bx - cx, cby = by - cy, cdx = dx - cx, cdy = dy - cy;
        // 叉积运算
        auto cross = [] (int ux, int uy, int vx, int vy) {
            return ux * vy - vx * uy;
        };
        // 判断线段 (ux, uy) -- (vx, vy) 是否包含 (mx, my)
        auto bothSide = [&] (int mx, int my, int ux, int uy, int vx, int vy) {
            double um = sqrt((ux - mx) * (ux - mx) + (uy - my) * (uy - my));
            double vm = sqrt((vx - mx) * (vx - mx) + (vy - my) * (vy - my));
            double uv = sqrt((vx - ux) * (vx - ux) + (vy - uy) * (vy - uy));
            return (ux - mx) * (vx - mx) <= 0 && (uy - my) * (vy - my) <= 0;
        };
        // 以 x 为第一关键字，y 为第二关键字比较两个点的大小
        auto cmp = [] (const Coor& u, const Coor& v) {
            if (u.size() == 0 || v.size() == 0) return v.size() == 0;
            return (u[0] != v[0]) ? (u[0] < v[0]) : (u[1] < v[1]);
        };
        // 共线处理和 T 形处理
        if (cross(cax, cay, cbx, cby) == 0 || cross(adx, ady, abx, aby) == 0) {
            bool aInCd = bothSide(ax, ay, cx, cy, dx, dy), bInCd = bothSide(bx, by, cx, cy, dx, dy);
            bool cInAb = bothSide(cx, cy, ax, ay, bx, by), dInAb = bothSide(dx, dy, ax, ay, bx, by);
            Coor ans;
            if (aInCd) ans = min(ans, Coor({(double)ax, (double)ay}), cmp) ;
            if (bInCd) ans = min(ans, Coor({(double)bx, (double)by}), cmp);
            if (cInAb) ans = min(ans, Coor({(double)cx, (double)cy}), cmp);
            if (dInAb) ans = min(ans, Coor({(double)dx, (double)dy}), cmp);
            return ans;
        }
        // 判断两条线段是否有公共点
        auto intersect = [&] () {
            return cross(acx, acy, abx, aby) * cross(adx, ady, abx, aby) <= 0 && cross(cax, cay, cdx, cdy) * cross(cbx, cby, cdx, cdy) <= 0;
        };
        if (!intersect()) {
            return Coor();
        }
        // 计算三角形 PQM 的面积
        auto getArea = [&] (int px, int py, int qx, int qy, int mx, int my) -> double {
            int mpx = px - mx, mpy = py - my, mqx = qx - mx, mqy = qy - my;
            return fabs(double(0.5) * cross(mpx, mpy, mqx, mqy));
        };
        // 定比分点
        double ck = getArea(ax, ay, bx, by, cx, cy), dk = getArea(ax, ay, bx, by, dx, dy);
        double k = ck / dk;
        double rx = (cx + k * dx) / (1 + k), ry = (cy + k * dy) / (1 + k);
        return Coor({rx, ry});
    }
};

// 线性代数
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)
#define det(a, b, c, d) (a*d-b*c)
class Solution{
public:
    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        //auto [x1, y1] = start1, [x2, y2] = end1, [x3, y3] = start2, [x4, y4] = end2;
        double x1 = start1[0], y1 = start1[1];
        double x2 = end1[0], y2 = end1[1];
        double x3 = start2[0], y3 = start2[1];
        double x4 = end2[0], y4 = end2[1];

        //double d = det(x1 - x2, x4 - x3, y1 - y2, y4 - y3);
        double d = (x1 - x2)*(y4 - y3) - (x4 - x3)*(y1 - y2);
        //double p = det(x4 - x2, x4 - x3, y4 - y2, y4 - y3);
        double p = (x4 - x2)*(y4 - y3) - (x4 - x3)*(y4 - y2);
        //double q = det(x1 - x2, x4 - x2, y1 - y2, y4 - y2);
        double q = (x1 - x2)*(y4 - y2) - (x4 - x2)*(y1 - y2);
        cout << "d:" << d << ", q:" << q << ", p:" << p << '\n';
        //相交不共线
        if(d != 0){
            double lam = p/d, eta = q/d;
            cout << "lam:" << lam << ", eta:" << eta << '\n';
            if (lam<0 || lam>1 || eta<0 || eta>1) return {};
            return {lam * x1 + (1 - lam) * x2, lam * y1 + (1 - lam) * y2};
        }
        //不相交
        if( p != 0 || q != 0) return {};
        //共线
        double t1 = min(max(y1,y2), max(y3,y4)), t2 = max(min(y1,y2), min(y3,y4)), tx2 = max(min(x1,x2), min(x3,x4));
        cout << t1 << ',' << t2 << '\n';
        if(t1>=t2)
            return {tx2, t2};

        return {};
    }
};
