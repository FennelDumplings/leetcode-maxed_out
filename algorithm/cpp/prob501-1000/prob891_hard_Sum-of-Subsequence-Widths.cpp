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

const int MOD = 1e9 + 7;
using ll = long long;

int quickpower(int a, int n, int mod)
{
    int ans = 1;
    while(n)
    {
        if(n & 1)
            ans = ((ll)ans * a) % mod;
        a = (ll)a * a % mod;
        n >>= 1;
    }
    return ans % mod;
}

class Solution {
public:
    int sumSubseqWidths(vector<int>& A) {
        sort(A.begin(), A.end());
        int n = A.size();
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            ans = (ans + (ll)A[i] * quickpower(2, i, MOD)) % MOD;
            ans = (ans - (ll)A[i] * quickpower(2, n - 1 - i, MOD) + MOD) % MOD;
        }
        return ans;
    }
};

// class Solution {
// public:
//     int sumSubseqWidths(vector<int>& A) {
//         sort(A.begin(), A.end());
//         int n = A.size();
//         long long ans = 0, p = 1, sum = 0; // p 是累计的次方数，sum 是累计 Y 的值
//         for(int i = 0; i < n; ++i)
//         {
//             // 此时 p = 2 ^ i
//             ans = (ans + A[i] * (p - 1) - sum) % MOD;
//             sum = (A[i] + sum * 2) % MOD;
//             p = p * 2 % MOD;
//         }
//         return (ans + MOD) % MOD;
//     }
//
// };
