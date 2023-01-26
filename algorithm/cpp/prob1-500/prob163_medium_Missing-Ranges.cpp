// prob163: Missing Ranges

/*
 * Given a sorted integer array nums, where the range of elements are in the inclusive range [lower, upper], return its missing ranges.
 */

/*
 * Example:
 * Input: nums = [0, 1, 3, 50, 75], lower = 0 and upper = 99,
 * Output: ["2", "4->49", "51->74", "76->99"]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        using ll = long long;
        if(nums.empty())
        {
            string item = to_string(lower);
            if(lower < upper)
                item += "->" + to_string(upper);
            return vector<string>{item};
        }
        vector<string> result;
        int n = nums.size();
        if(lower < nums[0])
        {
            string item = to_string(lower);
            if(lower + 1 < nums[0])
                item += "->" + to_string(nums[0] - 1);
            result.push_back(item);
        }
        int left = 0;
        while(left < n)
        {
            while(left + 1 < n && (ll)nums[left] + 1 >= (ll)nums[left + 1])
                ++left;
            if(left + 1 < n)
            {
                string item = to_string(nums[left] + 1);
                if(nums[left] + 2 < nums[left + 1])
                    item += "->" + to_string(nums[left + 1] - 1);
                result.push_back(item);
            }
            ++left;
        }
        if(nums[n - 1] < upper)
        {
            string item = to_string(nums[n - 1] + 1);
            if(nums[n - 1] + 1 < upper)
                item += "->" + to_string(upper);
            result.push_back(item);
        }
        return result;
    }
};
