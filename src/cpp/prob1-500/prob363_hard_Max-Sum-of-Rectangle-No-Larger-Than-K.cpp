// prob363: Max Sum of Rectangle No Larger Than K

/*
 * Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.
 */

/*
 * Example:
 * Input: matrix = [[1,0,1],[0,-2,3]], k = 2
 * Output: 2
 * Explanation: Because the sum of rectangle [[0, 1], [-2, 3]] is 2,
 *              and 2 is the max number no larger than k (k = 2).
 */

/*
 * Note:
 * The rectangle inside the matrix must have an area > 0.
 * What if the number of rows is much larger than the number of columns?
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(), m = matrix[0].size();

        vector<vector<int>> sums(n + 1, vector<int>(m + 1, 0));
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                sums[i + 1][j + 1] = sums[i + 1][j] + sums[i][j + 1] - sums[i][j] + matrix[i][j];

        int ans = INT_MIN;
        vector<int> vec(n);
        for(int j1 = 0; j1 < m; ++j1)
            for(int j2 = j1; j2 < m; ++j2)
            {
                for(int i = 0; i < n; ++i)
                    vec[i] = sums[i + 1][j2 + 1] - sums[i + 1][j1];
                ans = max(ans, maxSubArray(vec, k));
            }

        return ans;
    }

private:
    int maxSubArray(vector<int>& nums, int k)
    {
        using PII = pair<int, int>;
        vector<PII> sums(nums.size() + 1);
        sums[0] = {0, 0};
        int n = sums.size();
        for(int i = 1; i < n; ++i)
            sums[i] = {sums[i - 1].first + nums[i - 1], i};
        sort(sums.begin(), sums.end());
        int max_diff = INT_MIN;
        int i = n - 2, j = n - 1;
        while(i >= 0)
        {
            int diff = sums[i].first - sums[j].first;
            // [i..j]
            if(diff <= k)
            {
                if(sums[i].second > sums[j].second)
                    max_diff = max(max_diff, diff);
                --i;
            }
            else
            {
                --j;
                if(i == j)
                    --i;
            }
        }
        i = 0, j = 1;
        while(j < n)
        {
            int diff = sums[j].first - sums[i].first;
            if(diff <= k)
            {
                if(sums[j].second > sums[i].second)
                    max_diff = max(max_diff, diff);
                ++j;
            }
            else
            {
                ++i;
                if(i == j)
                    ++j;
            }
        }
        return max_diff;
    }
};

