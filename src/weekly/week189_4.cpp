// 20200517
// 4. 圆形靶内的最大飞镖数量

/*
 * 墙壁上挂着一个圆形的飞镖靶。现在请你蒙着眼睛向靶上投掷飞镖。
 * 投掷到墙上的飞镖用二维平面上的点坐标数组表示。飞镖靶的半径为 r 。
 * 请返回能够落在 任意 半径为 r 的圆形靶内或靶上的最大飞镖数。
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Mean-Shift
class Solution {
public:
    int numPoints(vector<vector<int>>& points, int r) {
        int n = points.size();
        int left = 1, right = n;
    }

private:
    bool _check(vector<vector<int>>& points, int k, int r)
    {
    }
};
