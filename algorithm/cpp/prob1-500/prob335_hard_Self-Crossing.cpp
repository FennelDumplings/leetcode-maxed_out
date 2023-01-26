// prob335: Self Crossing

/*
 * https://leetcode-cn.com/problems/self-crossing/
 */

#include <vector>

using namespace std;

struct Point
{
    int x, y;
    Point():x(0),y(0){}
    Point(int x, int y):x(x),y(y){}
};

class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        int n = x.size();
        if(n < 4) return false;
        vector<Point> p_prev(5);
        Point p;
        int ori = 0;
        for(int i = 0; i < 3; ++i)
        {
            Point p_next = step(ori, p, x[i]);
            p_prev[2 - i] = p_next;
            p = p_next;
            ori = (ori + 1) % 4;
        }
        // 第四步 a[3]
        Point p0 = p_prev[3];
        Point p4 = step(ori, p, x[3]);
        ori = (ori + 1) % 4;
        int state = -1;
        // 对比 p4 和 p_prev[3]
        if(p4.x <= p0.x && p4.y >= p0.y)
            return true;
        else if(p4.x < p0.x)
            state = 2; // 外螺旋
        else if(p4.x == p0.x)
            state = 1; // 预备内螺旋
        else
            state = 0; // 内螺旋
        p = p4; // 当前点
        // 第五步及以后
        for(int i = 4; i < n; ++i)
        {
            Point p_next = step(ori, p, x[i]);
            if(state == 1) // 预备内螺旋
            {
                // 判断线段 (p[i], p[i + 1]) 与线段 (p[i-5], p[i-4]) 是否有交点
                if(segment_cross(p_next, p_prev[3], ori))
                    return true;
                else
                    state = 0;
            }
            else if(state == 0) // 内螺旋
            {
                if(segment_cross(p_next, p_prev[1], ori))
                    return true;
            }
            else // 外螺旋
            {
                int s = line_2p(p_next, p_prev[2], p_prev[3], ori);
                if(s == 0) // 同一侧
                    state = 0;
                else if(s == 1) // p_next 落在直线上
                    state = 1;
            }
            for(int i = 4; i > 0; --i)
                p_prev[i] = p_prev[i - 1];
            p_prev[0] = p;
            p = p_next;
            ori = (ori + 1) % 4;
        }
        return false;
    }

private:
    // 上，右，下，左
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    bool segment_cross(const Point& p1, const Point& p2, int ori)
    {
        if(ori == 0) // 上
            return p1.y >= p2.y;
        if(ori == 1) // 右
            return p1.x >= p2.x;
        if(ori == 2) // 下
            return p1.y <= p2.y;
        // 左
        return p1.x <= p2.x;
    }

    int line_2p(const Point& p1, const Point& p2, const Point& p3, int ori)
    {
        if(ori == 0) // 上
        {
            if(p1.y > p2.y)
                return 2;
            else if(p1.y <= p2.y && p1.y >= p3.y)
                return 1;
            else
                return 0;
        }
        if(ori == 1) // 右
        {
            if(p1.x > p2.x)
                return 2;
            else if(p1.x <= p2.x && p1.x >= p3.x)
                return 1;
            else
                return 0;
        }
        if(ori == 2) // 下
        {
            if(p1.y < p2.y)
                return 2;
            else if(p1.y >= p2.y && p1.y <= p3.y)
                return 1;
            else
                return 0;
        }
        // 左
        if(p1.x < p2.x)
            return 2;
        else if(p1.x >= p2.x && p1.x <= p3.x)
            return 1;
        else
            return 0;
    }

    Point step(int ori, Point p, int l)
    {
        Point t;
        t.x = p.x + dx[ori] * l;
        t.y = p.y + dy[ori] * l;
        return t;
    }
};
