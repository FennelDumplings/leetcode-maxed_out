// prob493: Reverse Pairs

/*
 * Given an array nums, we call (i, j) an important reverse pair if i < j and nums[i] > 2*nums[j].
 * You need to return the number of important reverse pairs in the given array.
 */

/*
 * Example1:
 * Input: [1,3,2,3,1]
 * Output: 2
 * Example2:
 * Input: [2,4,3,5,1]
 * Output: 3
 */

/*
 * Note:
 * The length of the given array will not exceed 50,000.
 * All the numbers in the input array are in the range of 32-bit integer.
 */

#include <vector>
#include <algorithm>

using namespace std;

// 离散化 + 权值树状数组
class BIT {
public:
    BIT():sums(1, 0){}
    BIT(int n):sums(n + 1, 0){}

    void update(int index, int delta)
    {
        int n = sums.size();
        while(index < n)
        {
            sums[index] += delta;
            index += _lowbit(index);
        }
    }

    int query(int i)
    {
        int sum = 0;
        while(i > 0)
        {
            sum += sums[i];
            i -= _lowbit(i);
        }
        return sum;
    }

private:
    vector<int> sums;

    int _lowbit(int x)
    {
        return x & (-x);
    }
};

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();

        vector<ll> x; // 离散化后的值
        for(int i: nums)
        {
            x.push_back(i);
            x.push_back(2ll * i);
        }
        sort(x.begin(), x.end());
        x.erase(unique(x.begin(), x.end()), x.end());

        int m = x.size();
        BIT bit(m); // bit 内部对 m 做了 + 1
        bit.update(_find(nums[0], x), 1);
        int ans = 0;
        for(int i = 1; i < n; ++i)
        {
            ans += i - bit.query(_find(2ll * nums[i], x));
            bit.update(_find(nums[i], x), 1);
        }
        return ans;
    }

private:
    using ll = long long;

    int _find(ll v, const vector<ll>& x)
    {
        return lower_bound(x.begin(), x.end(), v) - x.begin() + 1;
    }
};

// CDQ 分治
// Modified Merge Sort
// 在归并排序的归并阶段统计一些信息
// Ref 面51
class Solution_2 {
public:
    int reversePairs(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        if(n == 1) return 0;
        return _mergesort(nums, 0, n - 1);
    }

private:
    using ll = long long;

    int _mergesort(vector<int>& nums, int left, int right)
    {
        int mid = left + (right - left) / 2;
        int res = 0;
        if(left == right) return 0;
        res += _mergesort(nums, left, mid);
        res += _mergesort(nums, mid + 1, right);
        res += _merge(nums, left, mid + 1, right);
        return res;
    }

    int _merge(vector<int>& nums, int left, int mid, int right)
    {
        //-------------------
        // 统计过程
        int i = left, j = mid;
        int res = 0;
        while(i < mid && j <= right)
        {
            if((ll)nums[i] > 2ll * nums[j])
            {
                res += mid - i;
                ++j;
            }
            else
                ++i;
        }
        //-------------------

        // 归并过程
        i = left, j = mid;
        int k = 0;
        vector<int> tmp(right - left + 1, 0);
        while(i < mid && j <= right)
        {
            if(nums[i] > nums[j])
            {
                tmp[k] = nums[j];
                ++k;
                ++j;
            }
            else
            {
                tmp[k] = nums[i];
                ++k;
                ++i;
            }
        }
        while(i < mid) tmp[k++] = nums[i++];
        while(j <= right) tmp[k++] = nums[j++];
        for(i = left, k = 0; i <= right; ++i, ++k)
            nums[i] = tmp[k];
        return res;
    }
};
