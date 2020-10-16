// prob1130: Minimum Cost Tree From Leaf Values

/*
 * https://leetcode-cn.com/problems/minimum-cost-tree-from-leaf-values/
 */

#include <vector>
#include <climits>

using namespace std;

struct Result
{
    int val; // 节点值
    int sum; // 子树各个节点值之和
    int max_leaf;
    Result(int val, int sum, int max_leaf):val(val),sum(sum),max_leaf(max_leaf){}
};

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        int sum = 0;
        for(int i: arr)
            sum += i;
        dp = vector<vector<Result>>(n, vector<Result>(n, Result(-1, -1, -1)));
        Result result = solve(arr, 0, n - 1);
        return result.sum - sum;
    }

private:
    vector<vector<Result>> dp;

    Result solve(const vector<int>& arr, int l, int r)
    {
        if(l == r)
            return Result(arr[l], arr[l], arr[l]);
        if(dp[l][r].val != -1)
            return dp[l][r];
        // l < r
        Result result(-1, INT_MAX, -1);
        for(int mid = l; mid < r; ++mid)
        {
            Result left = solve(arr, l, mid);
            Result right = solve(arr, mid + 1, r);
            int val = left.max_leaf * right.max_leaf;
            int max_leaf = max(left.max_leaf, right.max_leaf);
            int sum = val + left.sum + right.sum;
            if(sum < result.sum)
            {
                result.val = val;
                result.max_leaf = max_leaf;
                result.sum = sum;
            }
        }
        return dp[l][r] = result;
    }
};
