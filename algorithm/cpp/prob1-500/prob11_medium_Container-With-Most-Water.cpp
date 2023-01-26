// prob11: Container With Most Water

/*
 * Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai).
 * n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines,
 * which together with x-axis forms a container, such that the container contains the most water.
 * Note: You may not slant the container and n is at least 2.
 */

/*
 * Example:
 * Output: 49
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        if(height.empty()) return 0;
        int n = height.size();
        if(n == 1) return 0;
        int l = 0, r = n - 1;
        int result = 0;
        while(l < r)
        {
            int width = r - l;
            int h;
            if(height[l] <= height[r])
            {
                h = height[l];
                ++l;
            }
            else
            {
                h = height[r];
                --r;
            }
            result = max(result, width * h);
        }
        return result;
    }
};
