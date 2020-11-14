// prob1235: Maximum Profit in Job Scheduling

/*
 * https://leetcode-cn.com/problems/maximum-profit-in-job-scheduling/
 */

#include <vector>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        vec = startTime;
        vec.insert(vec.end(), endTime.begin(), endTime.end());
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        int m = vec.size();
        // 离散化后的时间范围为 [0..m-1]

        // dp[i] := 离散化后的时间范围为 [i..m-1] 时，最大利润
        // 初始化 dp[m] = 0
        // 答案 dp[0]
        // dp[i] 的转移：
        // 可选范围是起始时间 >= i 的 j，即
        // dp[i] = profit[j] + dp[endtime[j]+1]   startTime[j] >= i
        map<int, map<int, int, greater<int>>> items;
        int n = startTime.size();
        for(int i = 0; i < n; ++i)
            items[_find(startTime[i])][_find(endTime[i])] = profit[i];
        dp = vector<int>(m + 1, -1);
        dp[m] = 0;
        solve(items, 0);
        return dp[0];
    }

private:
    vector<int> vec; // 排序去重后的数据
    vector<int> dp;

    int solve(const map<int, map<int, int, greater<int>>>& items, int i)
    {
        if(dp[i] != -1)
            return dp[i];
        dp[i] = 0;
        // items 中找 items[j].s >= i 的
        auto it = items.lower_bound(i);
        if(it == items.end()) return dp[i];
        int right = (it -> second).begin() -> first;
        // int left = it -> first;
        // 优化: 起点在 [left, right] 范围的项目是本次转移需要考虑的
        while(it != items.end() && it -> first < right)
        {
            for(const auto &item: it -> second)
            {
                int e = item.first;
                int p = item.second;
                dp[i] = max(dp[i], p + solve(items, e));
            }
            ++it;
        }
        return dp[i];
    }

    int _find(int x) // 原值 -> 离散化后的值
    {
        auto it = lower_bound(vec.begin(), vec.end(), x);
        return it - vec.begin();
    }
};
