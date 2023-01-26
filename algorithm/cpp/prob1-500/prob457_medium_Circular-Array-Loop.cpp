// prob457: Circular Array Loop

/*
 * You are given a circular array nums of positive and negative integers.
 * If a number k at an index is positive, then move forward k steps. Conversely,
 * if it's negative (-k), move backward k steps. Since the array is circular,
 * you may assume that the last element's next element is the first element,
 * and the first element's previous element is the last element.
 * Determine if there is a loop (or a cycle) in nums. A cycle must start
 * and end at the same index and the cycle's length > 1. Furthermore,
 * movements in a cycle must all follow a single direction. In other words,
 * a cycle must not consist of both forward and backward movements.
 */

#include <vector>

using namespace std;

// 双指针
class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        if(nums.empty()) return false;
        int n = nums.size();
        if(n == 1) return false;

        vector<bool> state(n, false);
        for(int i = 0; i < n; ++i)
        {
            if(!state[i] && _is_cycle(nums, i, state))
                return true;
        }
        return false;
    }

private:
    bool _is_cycle(const vector<int>& nums, int start, vector<bool>& state)
    {
        // 若没有环，则中间一定某个地方出现了反向
        // 若又换，咋快慢指针会相遇
        bool direction = (nums[start] > 0); // false, 逆时针，true, 顺时针
        int i_slow = start, i_fast = start;
        while((nums[i_fast] > 0) == direction && (nums[_next_index(nums, i_fast)] > 0) == direction)
        {
            i_slow = _next_index(nums, i_slow);
            if(_next_index(nums, i_fast) == i_fast) return false; // 判断长度为1的环
            i_fast = _next_index(nums, i_fast);
            if(_next_index(nums, i_fast) == i_fast) return false;
            i_fast = _next_index(nums, i_fast);
            state[i_fast] = true;
            state[i_slow] = true;
            if(i_slow == i_fast)
                return true;
        }
        return false;
    }

    int _next_index(const vector<int>& nums, int index)
    {
        int n = nums.size();
        return (n + (nums[index] % n) + index) % n;
    }
};
