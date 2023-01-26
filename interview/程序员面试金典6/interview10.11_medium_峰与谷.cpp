// interview10.11: 峰与谷

/*
 * https://leetcode-cn.com/problemset/all/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        if(nums.empty()) return;
        int n = nums.size();
        if(n == 1) return;

        _threecolorsort(nums);
    }

private:
    void _threecolorsort(vector<int>& nums)
    {
        int n = nums.size();
        nth_element(nums.begin(), nums.begin() + n / 2, nums.end());
        int mid = nums[n / 2];

        int left = 0, right = n - 1;
        int l = left, r = right, cur = left;
        // [left, l)   < mid
        // [l, cur)    = mid
        // [cur, r]    未处理
        // (r, right]  > mid
        while(cur <= r)
        {
            if(nums[f(cur, n)] < mid)
                _swap(nums, cur++, l++);
            else if(nums[f(cur, n)] == mid)
                ++cur;
            else
                _swap(nums, cur, r--);
        }
    }

    int f(int i, int n) // 坐标映射
    {
        // 假id(做排序的id) -> 真实应该放到的 id
        // 偶数长度 3,7,2,6,1,5,0,4
        // 奇数数长度 4,8,3,7,2,6,1,5,0
        // i <= (n - 1)/2 的放下面, i >= (n - 1)/2 + 1 放上面
        if(n % 2 == 0)
        {
            if(i <= (n - 1) / 2)
                return n - 2 - i * 2;
            else
                return n - 1 - (i - (n + 1) / 2) * 2;
        }
        else
        {
            if(i <= (n - 1) / 2)
                return n - 1 - i * 2;
            else
                return n - 2 - (i - (n + 1) / 2) * 2;
        }
    }

    void _swap(vector<int>& nums, int i, int j)
    {
        int n = nums.size();
        int tmp = nums[f(i, n)];
        nums[f(i, n)] = nums[f(j, n)];
        nums[f(j, n)] = tmp;
    }
};
