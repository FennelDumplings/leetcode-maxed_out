// 20200531
// 1. 数组中两元素的最大乘积

#include <vector>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        int maxx, maxx2, minx, minx2;
        maxx = max(nums[0], nums[1]);
        maxx2 = min(nums[0], nums[1]);
        minx2 = max(nums[0], nums[1]);
        minx = min(nums[0], nums[1]);
        for(int i = 2; i < n; ++i)
        {
            int cur = nums[i];
            if(cur >= maxx)
            {
                maxx2 = maxx;
                maxx = cur;
            }
            else if(cur >= maxx2)
            {
                maxx2 = cur;
            }
            if(cur <= minx)
            {
                minx2 = minx;
                minx = cur;
            }
            else if(cur <= minx2)
            {
                minx2 = cur;
            }
        }
        return max((minx - 1) * (minx2 - 1), (maxx - 1) * (maxx2 - 1));
    }
};
