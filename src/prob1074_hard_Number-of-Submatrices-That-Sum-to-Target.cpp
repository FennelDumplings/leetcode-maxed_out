// prob1074: Number of Submatrices That Sum to Target

/*
 * https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()) return 0;
        int n = matrix.size();
        int m = matrix[0].size();

        sums2d = vector<vector<int> >(n + 1, vector<int>(m + 1, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                sums2d[i][j] = sums2d[i][j - 1] + sums2d[i - 1][j]
                    - sums2d[i - 1][j - 1] + matrix[i - 1][j - 1];

        int ans = 0;
        for(int i = 0; i < n; ++i)
            for(int l = 0; l <= i; ++l)
            {
                vector<int> nums(m);
                for(int j = 0; j < m; ++j)
                    nums[j] = sum_region(l, j, i, j);
                ans += solve1d(nums, target);
            }
        return ans;
    }

private:
    vector<vector<int>> sums2d;
    unordered_map<int, int> mapping;

    int solve1d(const vector<int>& nums, const int target)
    {
        int m = nums.size();
        mapping.clear();
        mapping[0] = 1;
        int sum = 0;
        int ans = 0;
        for(int j = 0; j < m; ++j)
        {
            sum += nums[j];
            int gap = sum - target;
            ans += mapping[gap];
            ++mapping[sum];
        }
        return ans;
    }

    int sum_region(int row1, int col1, int row2, int col2)
    {
        // row1 <= row2, col1 <= col2
        return sums2d[row2 + 1][col2 + 1] - sums2d[row2 + 1][col1]
            - sums2d[row1][col2 + 1] + sums2d[row1][col1];
    }
};
