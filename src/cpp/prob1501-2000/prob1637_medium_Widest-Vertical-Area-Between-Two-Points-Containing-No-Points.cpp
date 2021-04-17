// prob1637: Widest Vertical Area Between Two Points Containing No Points

/*
 * https://leetcode-cn.com/problems/widest-vertical-area-between-two-points-containing-no-points/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxWidthOfVerticalArea(vector<vector<int>>& points) {
        int n = points.size();
        vector<int> xs(n);
        for(int i = 0; i < n; ++i)
            xs[i] = points[i][0];
        sort(xs.begin(), xs.end());
        int ans = 0;
        for(int i = 0; i < n - 1; ++i)
            ans = max(ans, xs[i + 1] - xs[i]);
        return ans;
    }
};
