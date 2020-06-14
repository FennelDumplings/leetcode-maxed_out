// 20200613
// 3. 找两个和为目标值且不重叠的子数组

/*
 * 给你一个整数数组 arr 和一个整数值 target 。
 *
 * 请你在 arr 中找 两个互不重叠的子数组 且它们的和都等于 target 。可能会有多种方案，请你返回满足要求的两个子数组长度和的 最小值 。
 *
 * 请返回满足要求的最小长度和，如果无法找到这样的两个子数组，请返回 -1 。
 */

/*
 * 提示：
 *
 * 1 <= arr.length <= 10^5
 * 1 <= arr[i] <= 1000
 * 1 <= target <= 10^8
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        int left = 0;
        int right = left;
        int sum = 0;
        vector<vector<int>> ranges;
        while(left < n && right < n)
        {
            while(right < n)
            {
                sum += arr[right];
                if(sum == target)
                {
                    ranges.push_back({left, right});
                    break;
                }
                else if(sum > target)
                {
                    break;
                }
                else
                    ++right;
            }
            // cout << left << " " << right << endl;
            // sum >= target
            while(sum >= target)
            {
                sum -= arr[left];
                ++left;
                if(sum == target)
                {
                    ranges.push_back({left, right});
                }
            }
            ++right;
        }
        // for(auto r: ranges)
        // {
        //     for(auto i: r)
        //         cout << i << " ";
        //     cout << endl;
        // }
        sort(ranges.begin(), ranges.end(), Cmp());
        int m = ranges.size();
        int result = n * 2 + 1;
        for(int len = 1; len <= n - 1; ++len)
        {
            for(int i = 0; i + len < m; ++i)
            {
                int j = i + len;
                auto r1 = ranges[i];
                auto r2 = ranges[j];
                if(r1[0] > r2[1] || r1[1] < r2[0])
                    return r1[1] - r1[0] + r2[1] - r2[0];
            }
        }
        return -1;
        // for(int i = 0; i < m - 1; ++i)
        // {
        //     auto range1 = ranges[i];
        //     for(int j = i + 1; j < m; ++j)
        //     {
        //         auto range2 = ranges[j];
        //         if(range2[0] <= range1[1])
        //             continue;
        //         result = min(result, range1[1] - range1[0] + 1 + range2[1] - range2[0] + 1);
        //     }
        // }
        // if(result == n * 2 + 1)
        //     return -1;
        // return result;
    }

private:
    struct Cmp
    {
        boop operator()(const vector<int>& range1, const vector<int>& range2)
        {
            return range1[1] - range1[0] < range2[1] - range2[0];
        }
    }
};

