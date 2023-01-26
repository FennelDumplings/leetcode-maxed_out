// prob689: Maximum Sum of 3 Non-Overlapping Subarrays

/*
 * https://leetcode-cn.com/problems/maximum-sum-of-3-non-overlapping-subarrays/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        // 窗口有 n - k + 1 个
        int nw = n - k + 1;
        vector<int> w(nw, 0); // w[i] := 第 i 个窗口的和
        int w_sum = 0;
        for(int i = 0; i < k; ++i)
            w_sum += nums[i];
        w[0] = w_sum;
        for(int i = k; i < n; ++i)
        {
            w_sum -= nums[i - k];
            w_sum += nums[i];
            w[i - k + 1] = w_sum;
        }
        vector<int> left_max(nw), right_max(nw);
        left_max[0] = 0, right_max[nw - 1] = nw - 1;
        for(int i = 1; i < nw; ++i)
        {
            left_max[i] = left_max[i - 1];
            if(w[i] > w[left_max[i - 1]])
                left_max[i] = i;
        }
        for(int i = nw - 2; i >= 0; --i)
        {
            right_max[i] = right_max[i + 1];
            if(w[i] >= w[right_max[i + 1]])
                right_max[i] = i;
        }
        int max_sum = 0;
        vector<int> result(3);
        for(int j = k; j <= nw - k - 1; ++j)
        {
            int sum = w[left_max[j - k]] + w[j] + w[right_max[j + k]];
            if(sum > max_sum)
            {
                max_sum = sum;
                result[0] = left_max[j - k];
                result[1] = j;
                result[2] = right_max[j + k];
            }
        }
        return result;
    }
};
