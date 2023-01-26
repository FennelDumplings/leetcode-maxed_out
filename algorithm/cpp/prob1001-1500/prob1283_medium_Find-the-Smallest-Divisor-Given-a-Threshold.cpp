// prob1283: Find the Smallest Divisor Given a Threshold

/*
 * https://leetcode-cn.com/problems/find-the-smallest-divisor-given-a-threshold/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int maxx = nums[0];
        for(int i: nums)
        {
            maxx = max(maxx, i);
        }
        int left = 1, right = maxx;
        while(left < right)
        {
            int mid = (left + right) / 2;
            int res = check(nums, mid);
            if(res > threshold)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

private:
    int check(const vector<int>& nums, int mid)
    {
        int ans = 0;
        for(int i: nums)
        {
            ans += (i - 1) / mid + 1;
        }
        return ans;
    }
};
