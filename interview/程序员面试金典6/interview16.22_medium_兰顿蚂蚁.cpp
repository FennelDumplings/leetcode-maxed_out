// interview16.22: 兰顿蚂蚁

/*
 * https://leetcode-cn.com/problems/langtons-ant-lcci/
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Point
{
    int x, y;
    Point(int x, int y):x(x),y(y){}
    bool operator==(const Point& p) const
    {
        return x == p.x && y == p.y;
    }
};

struct MyHash
{
    int operator()(const Point& p) const
    {
        return p.x * 1e5 + p.y;
    }
};

class Solution {
public:
    vector<string> printKMoves(int K) {
        unordered_map<Point, char, MyHash> points;
        points[Point(0, 0)] = '_';
        Point iter(0, 0);
        char ori = 'R';
        for(int i = 1; i <= K; ++i)
        {
            if(points[iter] == '_')
            {
                points[iter] = 'X';
                right_rotate(ori);
            }
            else
            {
                points[iter] = '_';
                left_rotate(ori);
            }
            if(ori == 'L')
                --iter.y;
            else if(ori == 'U')
                --iter.x;
            else if(ori == 'R')
                ++iter.y;
            else if(ori == 'D')
                ++iter.x;
            if(points.count(iter) == 0)
                points[iter] = '_';
        }
        int minx = 1e6, miny = 1e6;
        int maxx = -1e6, maxy = -1e6;
        auto it = points.begin();
        while(it != points.end())
        {
            minx = min(minx, (it -> first).x);
            maxx = max(maxx, (it -> first).x);
            miny = min(miny, (it -> first).y);
            maxy = max(maxy, (it -> first).y);
            ++it;
        }
        int n = maxx - minx + 1, m = maxy - miny + 1;
        vector<string> result(n, string(m, '_'));
        it = points.begin();
        while(it != points.end())
        {
            int x = (it -> first).x - minx;
            int y = (it -> first).y - miny;
            if(it -> second == 'X')
                result[x][y] = 'X';
            ++it;
        }
        result[iter.x - minx][iter.y - miny] = ori;
        return result;
    }

private:
    void left_rotate(char& ori)
    {
            if(ori == 'L')
                ori = 'D';
            else if(ori == 'U')
                ori = 'L';
            else if(ori == 'R')
                ori = 'U';
            else if(ori == 'D')
                ori = 'R';
    }
    void right_rotate(char& ori)
    {
            if(ori == 'L')
                ori = 'U';
            else if(ori == 'U')
                ori = 'R';
            else if(ori == 'R')
                ori = 'D';
            else if(ori == 'D')
                ori = 'L';
    }
};
