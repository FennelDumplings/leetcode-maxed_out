// prob873: Length of Longest Fibonacci Subsequence

/*
 * A sequence X_1, X_2, ..., X_n is fibonacci-like if:
 *
 * n >= 3
 * X_i + X_{i+1} = X_{i+2} for all i + 2 <= n
 * Given a strictly increasing array A of positive integers forming a sequence, find the length of the longest fibonacci-like subsequence of A.  If one does not exist, return 0.
 *
 * (Recall that a subsequence is derived from another sequence A by deleting any number of elements (including none) from A, without changing the order of the remaining elements.  For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].)
 */

/*
 * Example 1:
 *
 * Input: [1,2,3,4,5,6,7,8]
 * Output: 5
 * Explanation:
 * The longest subsequence that is fibonacci-like: [1,2,3,5,8].
 * Example 2:
 *
 * Input: [1,3,7,11,12,14,18]
 * Output: 3
 * Explanation:
 * The longest subsequence that is fibonacci-like:
 * [1,11,12], [3,11,14] or [7,11,18].
 */

/*
 * Note:
 *
 * 3 <= A.length <= 1000
 * 1 <= A[0] < A[1] < ... < A[A.length - 1] <= 10^9
 * (The time limit has been reduced by 50% for submissions in Java, C, and C++.)
 */

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// 英文版 864 ms
// 中文版 TLE
// O((N^2)logN)
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        int n = A.size();
        // dp[i][j]:= [...,j, i] 的最大长度，从要么是0, 要么从3开始
        vector<vector<int> > dp(n, vector<int>(n, 0));
        int result = 0;
        for(int i = 2; i < n; ++i)
            for(int j = 1; j < i; ++j)
            {
                // [..k..j..i]
                // a[k] + a[j] = a[i]
                int target = A[i] - A[j];
                // 在 [0..j-1] 中找 target
                auto it = lower_bound(A.begin(), A.begin() + j - 1, target);
                if((*it) == target)
                {
                    int k = it - A.begin();
                    dp[i][j] = max(3, dp[j][k] + 1);
                    result = max(result, dp[i][j]);
                }
            }
        return result;
    }
};

// 转移时用哈希表辅助
// O(N^2)
// 中文版 500ms
class Solution_2 {
public:
    int lenLongestFibSubseq(vector<int>& A) {
        int n = A.size();
        // dp[i][j]:= [...,j, i] 的最大长度，从要么是0, 要么从3开始
        vector<vector<int> > dp(n, vector<int>(n, 0));
        unordered_map<int, int> mapping; // num -> idx
        for(int i = 0; i < n; ++i)
            mapping[A[i]] = i;
        int result = 0;
        for(int i = 2; i < n; ++i)
            for(int j = 1; j < i; ++j)
            {
                // [..k..j..i]
                // a[k] + a[j] = a[i]
                int target = A[i] - A[j];
                // 在 [0..j-1] 中找 target
                auto it = mapping.find(target);
                if(it != mapping.end() && (it -> second) < j)
                {
                    int k = it -> second;
                    dp[i][j] = max(3, dp[j][k] + 1);
                    result = max(result, dp[i][j]);
                }
            }
        return result;
    }
};
