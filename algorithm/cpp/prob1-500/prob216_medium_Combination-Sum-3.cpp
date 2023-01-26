// prob216: Combination Sum III

/*
 * Find all possible combinations of k numbers that add up to a number n, given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.
 * Note:
 * All numbers will be positive integers.
 * The solution set must not contain duplicate combinations.
 */

/*
 * Example 1:
 * Input: k = 3, n = 7
 * Output: [[1,2,4]]
 * Example 2:
 * Input: k = 3, n = 9
 * Output: [[1,2,6], [1,3,5], [2,3,4]]
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > result;
        vector<int> item;
        vector<bool> used(10, false);
        int start = 1; // 1 .. 9
        int sum = 0;
        dfs(result, item, sum, used, start, k, n);
        return result;
    }

private:
    void dfs(vector<vector<int> >& result, vector<int>& item, int& sum, vector<bool>& used, int start, int k, int n)
    {
        if(sum == n && (int)item.size() == k)
        {
            result.push_back(item);
            return;
        }
        if(sum > n || (int)item.size() > k)
            return;
        for(int i = start; i <= 9; ++i)
        {
            if(!used[i])
            {
                used[i] = true;
                item.push_back(i);
                sum += i;
                dfs(result, item, sum, used, i + 1, k, n);
                sum -= i;
                item.pop_back();
                used[i] = false;
            }
        }
    }
};
