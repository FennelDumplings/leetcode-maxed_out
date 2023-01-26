// prob254: Factor Combinations

/*
 * Numbers can be regarded as product of its factors. For example,
 * 8 = 2 x 2 x 2;
 *   = 2 x 4.
 *   Write a function that takes an integer n and return all possible combinations of its factors.
 *   Note:
 *   You may assume that n is always positive.
 *   Factors should be greater than 1 and less than n.
 */

/*
 * Example 1:
 * Input: 1
 * Output: []
 * Example 2:
 * Input: 37
 * Output:[]
 * Example 3:
 * Input: 12
 * Output:
 * [
 *   [2, 6],
 *   [2, 2, 3],
 *   [3, 4]
 * ]
 * Example 4:
 * Input: 32
 * Output:
 * [
 *   [2, 16],
 *   [2, 2, 8],
 *   [2, 2, 2, 4],
 *   [2, 2, 2, 2, 2],
 *   [2, 4, 4],
 *   [4, 8]
 * ]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> getFactors(int n) {
        if(n == 1) return {};
        // n > 1
        vector<vector<int>> result;
        vector<int> item;
        dfs(n, result, item);
        return result;
    }

private:
    void dfs(int n, vector<vector<int>>& result, vector<int>& item)
    {
        // n > 1
        // 枚举 n 的所有因子
        int start = 2;
        if(!item.empty())
            start = item.back();
        for(int i = start; i < n; ++i)
        {
            if(n % i != 0)
                continue;
            if(i > n / i || (!item.empty() && n / i < item.back()))
                break;
            result.push_back(item);
            result.back().push_back(i);
            result.back().push_back(n / i);
            item.push_back(i);
            dfs(n / i, result, item);
            item.pop_back();
        }
    }
};
