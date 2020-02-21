// prob189: Rotate Array

/*
 * Given an array, rotate the array to the right by k steps, where k is non-negative.
 */

/*
 * Example 1:
 * Input: [1,2,3,4,5,6,7] and k = 3
 * Output: [5,6,7,1,2,3,4]
 * Explanation:
 * rotate 1 steps to the right: [7,1,2,3,4,5,6]
 * rotate 2 steps to the right: [6,7,1,2,3,4,5]
 * rotate 3 steps to the right: [5,6,7,1,2,3,4]
 * Example 2:
 * Input: [-1,-100,3,99] and k = 2
 * Output: [3,99,-1,-100]
 * Explanation:
 * rotate 1 steps to the right: [99,-1,-100,3]
 * rotate 2 steps to the right: [3,99,-1,-100]
 */

/*
 * Note:
 * Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
 * Could you do it in-place with O(1) extra space?
 */

#include <vector>
#include <algorithm>

using namespace std;

// 基于反转
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        // reverse(nums.begin(), nums.end());
        // reverse(nums.begin(), nums.begin() + k);
        // reverse(nums.begin() + k, nums.end());
        _reverse(nums, 0, n - 1);
        _reverse(nums, 0, k - 1);
        _reverse(nums, k, n - 1);
    }

private:
    void _reverse(vector<int>& nums, int left, int right)
    {
        while(left < right)
        {
            int tmp = nums[left];
            nums[left] = nums[right];
            nums[right] = tmp;
            ++left;
            --right;
        }
    }
};


// 基于环状替换
class Solution_3 {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        // 有可能一个元素往前替换几次之后回到原位置了，那就把起始位置往前移动一位在开始替换
        int count = 0; // 记录替换次数，一共替换 n 次
        int start = 0; // start 记录一轮替换的原始位置
        int iter = start;
        int tmp = 0;
        while(count <= n - 1)
        {
            while(true)
            {
                int next = (iter + k) % n; // 下一个替换点
                if(next == start)
                {
                    start = (start + 1) % n;
                    iter = start;
                    ++count;
                    break;
                }
                tmp = nums[next];
                nums[next] = nums[start];
                nums[start] = tmp;
                iter = next;
                ++count;
                if(count == n - 1)
                    break;
            }
        }
    }
};

// 使用额外数组
// O(N) O(N)
class Solution_2 {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        vector<int> tmp(k, 0);
        for(int i = 0; i < k; ++i)
            tmp[i] = nums[n - k + i];
        for(int i = n - 1 - k; i >= 0; --i)
            nums[i + k] = nums[i];
        for(int i = 0; i < k; ++i)
            nums[i] = tmp[i];
    }
};

// 循环模拟(暴力)
// O(N^2) TLE
class Solution_1 {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        for(int i = 0; i < k; ++i)
            rotate1(nums);
    }

private:
    void rotate1(vector<int>& nums)
    {
        int n = nums.size();
        int tmp = nums[n - 1];
        for(int i = n - 2; i >= 0; --i)
        {
            nums[i + 1] = nums[i];
        }
        nums[0] = tmp;
    }
};


// STL
class Solution_STL {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        std::rotate(nums.begin(), nums.end() - k, nums.end());
    }
};
