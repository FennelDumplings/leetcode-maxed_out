// prob644: Maximum Average Subarray II

/*
 * Given an array consisting of n integers, find the contiguous subarray whose length is greater
 * than or equal to k that has the maximum average value. And you need to output the maximum average value.
 */

/*
 * Example 1:
 * Input: [1,12,-5,-6,50,3], k = 4
 * Output: 12.75
 * Explanation:
 * when length is 5, maximum average value is 10.8,
 * when length is 6, maximum average value is 9.16667.
 * Thus return 12.75.
 */

/*
 * Note:
 * 1 <= k <= n <= 10,000.
 * Elements of the given array will be in range [-10,000, 10,000].
 * The answer with the calculation error less than 10-5 will be accepted.
 */

#include <vector>

using namespace std;

class Solution {
public:
    double findMaxAverage(vector<int>& nums, int k) {
        int minx = nums[0], maxx = nums[0];
        for(int i: nums)
        {
            minx = min(minx, i);
            maxx = max(maxx, i);
        }
        double left = minx, right = maxx;
        while(left + EPS < right)
        {
            double mid = (left + right) / 2;
            if(check(nums, mid, k))
                right = mid;
            else
                left = mid;
        }
        return left;
    }

private:
    const double EPS = 1e-7;

    bool check(const vector<int>& nums, double mid, const int k)
    {
        int n = nums.size();
        double sum = 0.0;
        double prev = 0.0;
        for(int i = 0; i < k; ++i)
        {
            sum += nums[i] - mid;
        }
        if(sum + EPS > 0)
            return true;
        for(int i = k; i < n; ++i)
        {
            sum -= nums[i - k];
            sum += nums[i];
            prev = max(prev + nums[i - k] - mid, nums[i - k] - mid);
            if(sum + max(0.0, prev) + EPS > 0)
                return true;
        }
        return false;
    }
};
