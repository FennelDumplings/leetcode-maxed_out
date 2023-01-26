// prob1131: Maximum of Absolute Value Expression

/*
 * https://leetcode-cn.com/problems/maximum-of-absolute-value-expression/
 */

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int maxAbsValExpr(vector<int>& arr1, vector<int>& arr2) {
        int dx[4] = {-1, 1, -1, 1};
        int dy[4] = {-1, -1, 1, 1};
        int ans = 0;
        int n = arr1.size();
        for(int d = 0; d < 4; ++d)
        {
            int maxx = INT_MIN, minx = INT_MAX;
            for(int i = 0; i < n; ++i)
            {
                int x = arr1[i];
                int y = arr2[i];
                int z = i;
                maxx = max(maxx, x * dx[d]+ y * dy[d] + z);
                minx = min(minx, x * dx[d]+ y * dy[d] + z);
            }
            ans = max(ans, maxx - minx);
        }
        return ans;
    }
};
