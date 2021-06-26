// interview59-1: 滑动窗口的最大值

/*
 * https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/
 */

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(k == 0 || nums.empty()) return {};
        // 1 <= k <= n
        int n = nums.size();
        deque<int> deq;
        vector<int> result;
        deq.push_back(0);
        for(int i = 0; i < k; ++i)
        {
            while(!deq.empty() && nums[deq.back()] <= nums[i])
                deq.pop_back();
            deq.push_back(i);
        }
        result.push_back(nums[deq.front()]);
        for(int i = k; i < n; ++i)
        {
            if(deq.front() == i - k)
                deq.pop_front();
            while(!deq.empty() && nums[deq.back()] <= nums[i])
                deq.pop_back();
            deq.push_back(i);
            result.push_back(nums[deq.front()]);
        }
        return result;
    }
};
