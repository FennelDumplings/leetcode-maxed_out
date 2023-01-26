// prob1124: Longest Well-Performing Interval

/*
 * We are given hours, a list of the number of hours worked per day for a given employee.
 * A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
 * A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
 * Return the length of the longest well-performing interval.
 */

/*
 * Example 1:
 * Input: hours = [9,9,6,0,6,6,9]
 * Output: 3
 * Explanation: The longest well-performing interval is [9,9,6].
 */

/*
 * Constraints:
 * 1 <= hours.length <= 10000
 * 0 <= hours[i] <= 16
 */

#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

class Solution {
public:
    int longestWPI(vector<int>& hours) {
        if(hours.empty()) return 0;
        int n = hours.size();
        vector<int> sums(n + 1, 0);
        for(int i = 1; i <= n; ++i)
        {
            if(hours[i - 1] > 8)
                sums[i] = sums[i - 1] + 1;
            else
                sums[i] = sums[i - 1] - 1;
        }
        vector<int> veci, vecj;
        veci.push_back(0);
        int sum = 0;
        for(int i = 1; i <= n; ++i)
        {
            if(sums[i] < sum)
            {
                veci.push_back(i);
                sum = sums[i];
            }
        }
        sum = sums[n];
        vecj.push_back(n);
        for(int j = n - 1; j >= 0; --j)
        {
            if(sums[j] > sum)
            {
                vecj.push_back(j);
                sum = sums[j];
            }
        }
        int ni = veci.size(), nj = vecj.size();
        int j = 0;
        int result = 0;
        for(int i = ni - 1; i >=0; --i)
        {
            while(j < nj && sums[vecj[j]] <= sums[veci[i]])
                ++j;
            if(j < nj)
                result = max(result, vecj[j] - veci[i]);
        }
        return result;
    }
};

// 哈希表
class Solution_2 {
public:
    int longestWPI(vector<int>& hours) {
        if(hours.empty()) return 0;
        int result = 0;
        int n = hours.size();
        int net_cnt = 0; // 净的正向个数: 正向个数-负向个数
        unordered_map<int, int> mapping; // 前缀和 -> 最早出现索引
        mapping.insert(PII(0, 0));
        for(int i = 1; i <= n; ++i)
        {
            if(hours[i - 1] > 8)
                ++net_cnt;
            else
                --net_cnt;
            if(net_cnt > 0)
            {
                result = i;
                continue;
            }
            // net_cnt <= 0 找 net_cnt - 1 的最早出现位置.
            auto it = mapping.find(net_cnt - 1);
            if(it != mapping.end())
            {
                result = max(result, i - it -> second);
            }
            if(net_cnt < 0 && mapping[net_cnt] == 0)
                mapping[net_cnt] = i;
        }
        return result;
    }

private:
    using PII = pair<int, int>;
};
