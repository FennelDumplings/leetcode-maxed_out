// prob1266: Minimum Time Visiting All Points

/*
 * https://leetcode-cn.com/problems/minimum-time-visiting-all-points/
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int ans = 0;
        int n = points.size();
        for(int i = 0; i < n - 1; ++i)
        {
            int x = abs(points[i][0] - points[i + 1][0]);
            int y = abs(points[i][1] - points[i + 1][1]);
            ans += min(x, y);
            ans += max(x, y) - min(x, y);
        }
        return ans;
    }
};
