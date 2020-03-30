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
#include <queue>
#include <unordered_map>

using namespace std;

// multiset 用法
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k)
    {
        vector<double> result;
        multiset<int> setting(nums.begin(), nums.begin() + k);

        auto mid = next(setting.begin(), k / 2);

        for (int i = k;; i++) {

            // Push the current median
            result.push_back(((double)(*mid) + *next(mid, k % 2 - 1)) * 0.5);

            // If all done, break
            if (i == (int)nums.size())
                break;

            // Insert incoming element
            setting.insert(nums[i]);
            if (nums[i] < *mid)
                mid--;                  // same as mid = prev(mid)

            // Remove outgoing element
            if (nums[i - k] <= *mid)
                mid++;                  // same as mid = next(mid)

            setting.erase(setting.lower_bound(nums[i - k]));
        }

        return result;
    }
};

// 双堆模式
class Solution_2 {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        unordered_map<int, int> mapping;
        priority_queue<int> max_heap; // 大顶堆，存较小的一半
        priority_queue<int, vector<int>, greater<int> > min_heap; // 小顶堆，存较大的一半

        int i = 0; // 划窗的当前值

        // 堆的初始化
        while(i < k)
        {
            max_heap.push(nums[i]);
            ++i;
        }
        for(int j = 0; j < k / 2; ++j)
        {
            min_heap.push(max_heap.top());
            max_heap.pop();
        }

        // 正式迭代
        while(true)
        {
            double cur_median;
            if(k & 1)
                cur_median = max_heap.top();
            else
                cur_median = ((double)max_heap.top() + min_heap.top()) * 0.5;
            result.push_back(cur_median);

            if(i >= (int)nums.size()) break;

            int out_num = nums[i - k];
            int in_num = nums[i];
            ++i;
            int balance = 0;

            // 处理 out_num 出窗
            balance += (out_num <= max_heap.top() ? -1 : 1);
            mapping[out_num]++;

            // 处理 in_num 入窗
            if(!max_heap.empty() && in_num <= max_heap.top())
            {
                balance++;
                max_heap.push(in_num);
            }
            else
            {
                balance--;
                min_heap.push(in_num);
            }

            // 重平衡
            if(balance < 0)
            {
                max_heap.push(min_heap.top());
                min_heap.pop();
                balance++;
            }
            if(balance > 0)
            {
                min_heap.push(max_heap.top());
                max_heap.pop();
                balance--;
            }

            // 删除无效的元素
            while(mapping[max_heap.top()])
            {
                mapping[max_heap.top()]--;
                max_heap.pop();
            }
            while(!min_heap.empty() && mapping[min_heap.top()])
            {
                mapping[min_heap.top()]--;
                min_heap.pop();
            }
        }
        return result;
    }
};
