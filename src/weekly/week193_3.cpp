// 20200614
// 3. 制作 m 束花所需的最少天数

/*
 * 给你一个整数数组 bloomDay，以及两个整数 m 和 k 。
 *
 * 现需要制作 m 束花。制作花束时，需要使用花园中 相邻的 k 朵花 。
 *
 * 花园中有 n 朵花，第 i 朵花会在 bloomDay[i] 时盛开，并可以用于一束花中。
 *
 * 请你返回从花园中摘 m 束花需要等待的最少的天数。如果不能摘到 m 束花则返回 -1 。
 */

#include <vector>
#include <climits>

using namespace std;


class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        int min_day = INT_MAX;
        int max_day = INT_MIN;
        for(int day: bloomDay)
        {
            min_day = min(min_day, day);
            max_day = max(max_day, day);
        }
        int left = min_day, right = max_day;
        cout << left << " " << right << endl;
        while(left < right)
        {
            int mid = left + (right - left) / 2;
            if(check(bloomDay, mid, m, k))
                right = mid;
            else
                left = mid + 1;
        }
        if(left == max_day)
        {
            if(check(bloomDay, max_day, m, k))
                return max_day;
            else
                return -1;
        }
        return left;
    }

private:
    bool check(const vector<int>& bloomDay, int day, int m, int k)
    {
        int n = bloomDay.size();
        vector<bool> bloom(n, false);
        for(int i = 0; i < n; ++i)
        {
            if(bloomDay[i] <= day)
                bloom[i] = true;
        }
        // bloom 上是否有 m 个长为 k 的 true 窗口
        int cnt = 0;
        int left = 0;
        while(left + k <= n)
        {
            while(left < n && !bloom[left])
                ++left;
            if(left + k > n)
                break;
            int right = left;
            while(right - left < k && bloom[right])
            {
                ++right;
            }
            if(right - left == k)
                ++cnt;
            left = right;
        }
        return cnt >= m;
    }
};
