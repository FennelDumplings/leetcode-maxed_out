// prob1030: Matrix Cells in Distance Order

/*
 * https://leetcode-cn.com/problems/matrix-cells-in-distance-order/
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Cmp
{
    int r0, c0;
    Cmp(int r0, int c0):r0(r0),c0(c0){}
    bool operator()(const vector<int>& p1, const vector<int>& p2) const
    {
        return abs(p1[0] - r0) + abs(p1[1] - c0) < abs(p2[0] - r0) + abs(p2[1] - c0);
    }
};

class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<vector<int>> result;
        for(int i = 0; i < R; ++i)
            for(int j = 0; j < C; ++j)
                result.push_back({i, j});
        sort(result.begin(), result.end(), Cmp(r0, c0));
        return result;
    }
};
