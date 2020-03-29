// prob480: Sliding Window Median

/*
 * Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value.
 * So the median is the mean of the two middle value.
 * Examples:
 * [2,3,4] , the median is 3
 * [2,3], the median is (2 + 3) / 2 = 2.5
 * Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right.
 * You can only see the k numbers in the window. Each time the sliding window moves right by one position.
 * Your job is to output the median array for each window in the original array.
 */

/*
 * Note:
 * You may assume k is always valid, ie: k is always smaller than input array's size for non-empty array.
 * Answers within 10^-5 of the actual value will be accepted as correct.
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        bool odd = (k % 2 == 1);
        multiset<int> setting;
        for(int i = 0; i < k; ++i)
            setting.insert(nums[i]);
        auto median_iter = setting.begin();
        for(int i = 1; i <= k / 2; ++i)
            ++median_iter;
        vector<double> result(n + 1 - k, 0.0);
        _update_median(result, 0, median_iter, odd);
        for(int i = 1; i <= n - k; ++i)
        {
            // 出窗: nums[i - 1]
            // 进窗: nums[i + k - 1]
            if(nums[i - 1] == nums[i + k - 1]) continue;
            auto it = setting.find(nums[i - 1]);
            bool erase_median_iter = (it == median_iter);
            int cur_median = (*median_iter);
            if(erase_median_iter)
                median_iter = setting.erase(it);
            else
                setting.erase(it);
            setting.insert(nums[i + k - 1]);
            if(nums[i + k - 1] <= cur_median && nums[i - 1] > cur_median)
                --median_iter;
            else if(nums[i + k - 1] > cur_median && nums[i - 1] < cur_median)
                ++median_iter;
            else if(nums[i - 1] == cur_median)
            {
                if(erase_median_iter && nums[i + k - 1] <= cur_median)
                    --median_iter;
                else if(!erase_median_iter && nums[i + k - 1] > cur_median)
                    ++median_iter;
            }
            _update_median(result, i, median_iter, odd);
        }
        return result;
    }

private:
    void _update_median(vector<double>& result, int idx, multiset<int>::iterator iter, bool odd)
    {
        result[idx] = (double)(*iter);
        if(!odd)
        {
            --iter;
            result[idx] = (result[idx] + (*iter)) / 2;
        }
    }
};
