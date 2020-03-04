// prob77: Combinations

/*
 * Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.
 */

/*
 * Example:
 *
 * Input: n = 4, k = 2
 * Output:
 * [
 *   [2,4],
 *   [3,4],
 *   [2,3],
 *   [1,2],
 *   [1,3],
 *   [1,4],
 * ]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        if(n < 1) return vector<vector<int> >();
        if(k > n) return vector<vector<int> >();
        // n >= 1, k <= n
        int pos = 1;
        vector<vector<int> > results;
        vector<int> result_item;
        dfs(results, result_item, pos, n, k);
        return results;
    }

private:
    void dfs(vector<vector<int> >& results, vector<int>& result_item, int pos, int n, int k)
    {
        int cur_len = result_item.size();
        if(cur_len == k)
        {
            results.push_back(result_item);
            return;
        }
        if(n - pos + 1 + cur_len < k) return; // 剪枝
        if(pos > n) return;

        result_item.push_back(pos);
        dfs(results, result_item, pos + 1, n, k);
        result_item.pop_back();
        dfs(results, result_item, pos + 1, n, k);
    }
};

// DP: 利用组合的递推式
// C(n, k) = C(n - 1, k - 1) + C(n - 1, k - 1)
class Solution_2 {
public:
    vector<vector<int>> combine(int n, int k) {
        if(n < 1) return vector<vector<int> >();
        if(k > n) return vector<vector<int> >();
        // k == 1 和 n == k 是递归的关键
        if(k == 1)
        {
            vector<vector<int> > results;
            for(int i = 1; i <= n; ++i)
                results.push_back(vector<int>({i}));
            return results;
        }
        if (n == k)
        {
            vector<int> row;
            for (int i = 1; i <= n; ++i)
                row.push_back(i); // select all
            vector<vector<int> > results;
            results.push_back(row);
            return results;
        }

        vector<vector<int> > results = combine(n - 1, k - 1);
        for(vector<int>& result_item: results)
            result_item.push_back(n);

        vector<vector<int> > results2 = combine(n - 1, k);
        results.insert(results.end(), results2.begin(), results2.end());
        return results;
    }
};

// 二进制字典序
// e.g. 1, 2, 3, 4  C(4, 2)
// 0 0 1 1
// 0 1 0 1
// 0 1 1 0
// 1 0 0 1
// 1 0 1 0
// 1 1 0 0
// 性能最优
class Solution_3 {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> nums(k, 0);
        for(int i = 1; i <= k; ++i)
            nums[i - 1] = i;
        nums.push_back(n + 1); // 哨兵

        vector<vector<int> > results;
        int j = 0;
        while(j < k)
        {
            results.push_back(vector<int>(nums.begin(), nums.begin() + k));
            j = 0;
            while(j < k && nums[j + 1] == nums[j] + 1)
            {
                nums[j] = j + 1; // 关键一行
                ++j;
            }
            ++nums[j];
        }
        return results;
    }
};
