

#include <vector>
#include <algorithm>

using namespace std;

struct Point
{
    int id, x, y, v;
    Point(int id, int x, int y, int v):id(id),x(x),y(y),v(v){}
};

struct Cmp
{
    bool operator()(const Point& p1, const Point& p2) const
    {
        return p1.v < p2.v;
    }
};

class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<Point> points;
        int id = 0;
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                points.emplace_back(id++, i, j, matrix[i][j]);
        sort(points.begin(), points.end(), Cmp());
    }
};
