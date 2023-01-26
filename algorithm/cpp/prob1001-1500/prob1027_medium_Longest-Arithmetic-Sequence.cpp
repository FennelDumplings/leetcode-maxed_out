// prob1027: Longest Arithmetic Sequence

/*
 * Given an array A of integers, return the length of the longest arithmetic subsequence in A.
 */

/*
 * Example 1:
 *
 * Input: [3,6,9,12]
 * Output: 4
 * Explanation:
 * The whole array is an arithmetic sequence with steps of length = 3.
 * Example 2:
 *
 * Input: [9,4,7,2,10]
 * Output: 3
 * Explanation:
 * The longest arithmetic subsequence is [4,7,10].
 * Example 3:
 *
 * Input: [20,1,15,3,10,5,8]
 * Output: 4
 * Explanation:
 * The longest arithmetic subsequence is [20,15,10,5].
 */

/*
 * Note:
 *
 * 2 <= A.length <= 2000
 * 0 <= A[i] <= 10000
 */

#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

// dp[i][j] := 以 j, i 结尾，其中 j 用哈希表维护，只存有意义的
class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        int n = A.size();
        vector<unordered_map<int, int>> dp(n, unordered_map<int, int>());
        unordered_map<int, int> mapping; // d -> max_len
        for(int i = 1; i < n; ++i)
        {
            int d = A[i] - A[0];
            dp[i][d] = 2;
            mapping[d] = 2;
        }
        for(int i = 2; i < n; ++i)
        {
            for(int j = 1; j <= i - 1; ++j)
            {
                int d = A[i] - A[j];
                if(dp[j].find(d) != dp[j].end())
                {
                    dp[i][d] = dp[j][d] + 1;
                }
                else
                    dp[i][d] = 2;
                mapping[d] = max(mapping[d], dp[i][d]);
            }
        }
        int result = 0;
        for(auto iter: mapping)
            result = max(result, iter.second);
        return result;
    }
};

// j 不用哈希表
// 288ms
class Solution_2 {
public:
    int longestArithSeqLength(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> dp(n, vector<int>(n, 2));
        unordered_map<int, set<int>> mapping; // num -> idxs
        for(int i = 0; i < n; ++i)
            mapping[A[i]].insert(i);
        int result = 2;
        for(int i = 1; i < n; ++i)
        {
            for(int j = 0; j <= i - 1; ++j)
            {
                int d = A[i] - A[j];
                int target = A[j] - d;
                // [0..j-1] 中找 A[k] = target
                auto it = mapping.find(target);
                if(it == mapping.end())
                    continue;
                // idxs 中大于等于 j 的最小位置 idx_it
                // --idx_it 为小于 j 的最大位置
                auto idx_it = (it -> second).lower_bound(j);
                if(idx_it == (it -> second).begin())
                    continue;
                --idx_it;
                int k = *idx_it;
                dp[i][j] = dp[j][k] + 1;
                result = max(result, dp[i][j]);
            }
        }
        return result;
    }
};
