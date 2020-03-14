// prob891: Sum of Subsequence Widths

/*
 * Given an array of integers A, consider all non-empty subsequences of A.
 * For any sequence S, let the width of S be the difference between the maximum and minimum element of S.
 * Return the sum of the widths of all subsequences of A.
 * As the answer may be very large, return the answer modulo 10^9 + 7.
 */

/*
 * Example 1:
 * Input: [2,1,3]
 * Output: 6
 * Explanation:
 * Subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
 * The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
 * The sum of these widths is 6.
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumSubseqWidths(vector<int>& A) {
        int mod = 1e9 + 7;

        sort(A.begin(), A.end());
        long long res = 0, p = 1, sum = 0; // p 是累计的次方数，sum 是累计 Y 的值
        for(auto x: A)
        {
            res = (res + x * (p - 1) - sum) % mod;
            sum = (x + sum * 2) % mod;
            p = p * 2 % mod;
        }
        return (res + mod) % mod;
    }
};
