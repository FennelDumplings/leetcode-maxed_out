// Prob812 Largest Triangle Area

/*
 * You have a list of points in the plane. Return the area of the largest triangle that can be formed by any 3 of the points.
 */

/*
 * Example:
 * Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
 * Output: 2
 * Explanation:
 * The five points are show in the figure below. The red triangle is the largest.
 */

/* Note
 * 3 <= points.length <= 50.
 * No points will be duplicated.
 *  -50 <= points[i][j] <= 50.
 * Answers within 10^-6 of the true value will be accepted as correct.
 */

#include <vector>
#include <cmath>

using namespace std;

// 三角形面积，向量的叉积
// 三个点 (x1, y1), (x2, y2), (x3, y3)
// 两个向量 (x2-x1, y2-y1) (x3-x1, y3-y1)
// 叉积 (x2-x1)(y3-y1)-(x3-x1)(y2-y1)
// 面积 取绝对值后除以2
class Solution {
public:
    // 暴力
    double largestTriangleArea(vector<vector<int>>& points) {
        double result = 0.0;
        int n = points.size();
        for(int i = 0; i < n - 2; ++i)
            for(int j = i + 1; j < n - 1; ++j)
                for(int k = j + 1; k < n; ++k)
                    result = max(result, triangle_area(points, i, j, k));
        return result;
    }

private:
    double triangle_area(const vector<vector<int> >& points, int i, int j, int k)
    {
        // 可以把两个向量的终点的 x, y 分别写出来，更清晰
        double cross_product = (points[j][0] - points[i][0]) * (points[k][1] - points[i][1])
            - (points[k][0] - points[i][0]) * (points[j][1] - points[i][1]);
        return abs(cross_product) / 2.0;
    }
};



