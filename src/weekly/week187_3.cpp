// 3.  绝对差不超过限制的最长连续子数组

/*
 * 给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。
 * 如果不存在满足条件的子数组，则返回 0 。
 */

/*
 * 示例 1：
 * 输入：nums = [8,2,4,7], limit = 4
 * 输出：2
 * 解释：所有子数组如下：
 * [8] 最大绝对差 |8-8| = 0 <= 4.
 * [8,2] 最大绝对差 |8-2| = 6 > 4.
 * [8,2,4] 最大绝对差 |8-2| = 6 > 4.
 * [8,2,4,7] 最大绝对差 |8-2| = 6 > 4.
 * [2] 最大绝对差 |2-2| = 0 <= 4.
 * [2,4] 最大绝对差 |2-4| = 2 <= 4.
 * [2,4,7] 最大绝对差 |2-7| = 5 > 4.
 * [4] 最大绝对差 |4-4| = 0 <= 4.
 * [4,7] 最大绝对差 |4-7| = 3 <= 4.
 * [7] 最大绝对差 |7-7| = 0 <= 4.
 * 因此，满足题意的最长子数组的长度为 2 。
 * 示例 2：
 * 输入：nums = [10,1,2,4,7,2], limit = 5
 * 输出：4
 * 解释：满足题意的最长子数组是 [2,4,7,2]，其最大绝对差 |2-7| = 5 <= 5 。
 * 示例 3：
 * 输入：nums = [4,2,2,2,4,4,2,2], limit = 0
 * 输出：3
 */

/*
 * 提示：
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^9
 * 0 <= limit <= 10^9
 */

#include <vector>
#include <math>
#include <deque>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        // 值域二分
        int n = nums.size();
        if(n == 1) return 1;
        int left = 2, right = n;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            if(_check(nums, mid, limit))
                left = mid;
            else
                right = mid - 1;
        }
        if(left > 2) return left;
        if(_check(nums, 2, limit)) return 2;
        else return 0;
    }

private:
    bool _check(const vector<int>& nums, int mid, int limit)
    {
        // nums 中是否存在某个长为 len 的区间，该区间满足条件
        // 若不存在，则 mid 猜大了，right = mid - 1
        // 若存在，则 mid 为答案或者猜小了，left = mid
        int n = nums.size();
        vector<int> mins = minSlidingWindow(nums, mid);
        vector<int> maxs = maxSlidingWindow(nums, mid);
        //for(int a: mins) cout << a << " ";
        //cout << endl;
        //for(int a: maxs) cout << a << " ";
        //cout << endl;
        int N = mins.size();
        for(int i = 0; i < N; ++i)
            if(maxs[i] - mins[i] <= limit)
                return true;
        return false;
    }

    vector<int> minSlidingWindow(const vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = min(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        deque<int> dq;
        vector<int> result;
        for(int i = 0; i < k; ++i)
        {
            // 插入 i 前先出队
            while(!dq.empty() && nums[dq.back()] >= nums[i])
                dq.pop_back();
            dq.push_back(i);
        }
        result.push_back(nums[dq.front()]);
        for(int i = k; i < n; ++i)
        {
            if(!dq.empty() && dq.front() <= i - k)
                dq.pop_front();
            while(!dq.empty() && nums[dq.back()] >= nums[i])
                dq.pop_back();
            dq.push_back(i);
            result.push_back(nums[dq.front()]);
        }
        return result;
    }

    vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
        if(nums.empty()) return vector<int>();
        int n = nums.size();
        if(n <= k)
        {
            int mx = nums[0];
            for(int i = 1; i < n; ++i)
                mx = max(mx, nums[i]);
            return vector<int>({mx});
        }
        // 滑动 n - k 次
        // 0..k-1
        deque<int> dq;
        vector<int> result;
        for(int i = 0; i < k; ++i)
        {
            // 插入 i 前先出队
            while(!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            dq.push_back(i);
        }
        result.push_back(nums[dq.front()]);
        for(int i = k; i < n; ++i)
        {
            if(!dq.empty() && dq.front() <= i - k)
                dq.pop_front();
            while(!dq.empty() && nums[dq.back()] <= nums[i])
                dq.pop_back();
            dq.push_back(i);
            result.push_back(nums[dq.front()]);
        }
        return result;
    }
};
