// preb31: Next Permutation

/*
 * mplement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
 * The replacement must be in-place and use only constant extra memory.
 */

/*
 * Example
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        // 找到从 n-1 开始往左，第一个不单调不降的位置 t
        int t = n - 2;
        while(t >= 0 && nums[t] >= nums[t + 1])
            --t;
        if(t < 0)
            reverse(nums.begin(), nums.end());
        else
        {
            int k = n - 1;
            while(k > t && nums[t] >= nums[k])
                --k;
            swap(nums[t], nums[k]);
            reverse(nums.begin() + t + 1, nums.end());
        }
    }
};

class Solution_2 {
public:
    void nextPermutation(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;
        // 找到从 n-1 开始往右，第一个不单调不降的位置 t
        int t = n - 2;
        int mx = nums[n - 1];
        while(t >= 0 && nums[t] >= mx)
        {
            mx = nums[t];
            --t;
        }
        if(t < 0)
            _reverse(nums, 0, n - 1);
        else
        {
            int k = n - 1;
            while(k > t && nums[t] >= nums[k])
            {
                --k;
            }
            // a[..,t,t+1,..k-1,k..n-1] -> a[..,k..n-1,t,t+1..k-1]
            // 子数组 a[t..k-1,k..n-1] 在 k 点旋转 leetcode 189，移动 n - k 次
            _rotate(nums, t, k);
            // a[t+1..t+(n-k)-1], a[t+(n-k)+1..n-1] 分别翻转
            _reverse(nums,t + 1, n - (k - t) - 1);
            _reverse(nums, n - (k - t) + 1, n - 1);
        }
    }

private:
    void _rotate(vector<int>& nums, int t, int k)
    {
        // leetcode 189
        std::rotate(nums.begin() + t, nums.begin() + k, nums.end());
    }

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

// STL
class Solution_STL {
public:
    void nextPermutation(vector<int>& nums) {
        next_permutation(nums.begin(),nums.end());
    }
};
