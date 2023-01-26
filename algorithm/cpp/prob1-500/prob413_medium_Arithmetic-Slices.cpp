// prob413: Arithmetic Slices

/*
 * A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
 * A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.
 * A slice (P, Q) of array A is called arithmetic if the sequence:
 * A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.
 * The function should return the number of arithmetic slices in the array A.
 */

/*
 * Example:
 * A = [1, 2, 3, 4]
 * return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        if(n < 3) return 0;
        vector<int> dp(n, 0);
        for(int i = 2; i < n; ++i)
        {
            if(A[i] - A[i - 1] == A[i - 1] - A[i - 2])
                dp[i] = 1 + dp[i - 1];
        }
        int ans = 0;
        for(int i: dp)
            ans += i;
        return ans;
    }
};
