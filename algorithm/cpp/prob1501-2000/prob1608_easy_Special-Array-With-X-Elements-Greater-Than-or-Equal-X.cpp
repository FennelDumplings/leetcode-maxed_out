// prob1608: Special Array With X Elements Greater Than or Equal X

/*
 * https://leetcode-cn.com/problems/special-array-with-x-elements-greater-than-or-equal-x/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n;
        while(left < right)
        {
            int mid = (left + right) / 2;
            int cnt = check(nums, mid);
            if(cnt > mid)
                left = mid + 1;
            else
                right = mid;
        }
        return check(nums, left) == left ? left : -1;
    }

private:
    int check(const vector<int>& nums, int x)
    {
        // >= x 的元素个数
        int cnt  = 0;
        for(int i: nums)
            if(i >= x)
                ++cnt;
        return cnt;
    }
};
