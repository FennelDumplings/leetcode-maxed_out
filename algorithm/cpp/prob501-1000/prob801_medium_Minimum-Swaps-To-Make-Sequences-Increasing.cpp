// prob801: Minimum Swaps To Make Sequences Increasing

/*
 * We have two integer sequences A and B of the same non-zero length.
 * We are allowed to swap elements A[i] and B[i].  Note that both elements are in the same index position in their respective sequences.
 * At the end of some number of swaps, A and B are both strictly increasing.  (A sequence is strictly increasing if and only if A[0] < A[1] < A[2] < ... < A[A.length - 1].)
 * Given A and B, return the minimum number of swaps to make both sequences strictly increasing.  It is guaranteed that the given input always makes it possible.
 */

/*
 * Example:
 * Input: A = [1,3,5,4], B = [1,2,3,7]
 * Output: 1
 * Explanation:
 * Swap A[3] and B[3].  Then the sequences are:
 * A = [1, 3, 5, 7] and B = [1, 2, 3, 4]
 * which are both strictly increasing.
 */

/*
 * Note:
 * A, B are arrays with the same length, and that length will be in the range [1, 1000].
 * A[i], B[i] are integer values in the range [0, 2000].
 */

#include <vector>
#include <climits>

using namespace std;

// DP
class Solution {
public:
    int minSwap(vector<int>& A, vector<int>& B) {
        int n = A.size();
        // vector<int> swap(n, INT_MAX);
        // vector<int> keep(n, INT_MAX);
        // swap[0] = 1, keep[0] = 0;
        int prev_swap = 1, prev_keep = 0;
        int swap = INT_MAX, keep = INT_MAX;
        for(int i = 1; i < n; ++i)
        {
            swap = INT_MAX, keep = INT_MAX;
            if(A[i - 1] < A[i] && B[i - 1] < B[i])
            {
                // keep[i] = keep[i - 1];
                // swap[i] = swap[i - 1] + 1;
                keep = prev_keep;
                swap = prev_swap + 1;
            }
            if(B[i - 1] < A[i] && A[i - 1] < B[i])
            {
                // swap[i] = min(swap[i], keep[i - 1] + 1);
                // keep[i] = min(keep[i], swap[i - 1]);
                swap = min(swap, prev_keep + 1);
                keep = min(keep, prev_swap);
            }
            prev_keep = keep;
            prev_swap = swap;
        }
        // return min(swap[n - 1], keep[n - 1]);
        return min(swap, keep);
    }
};
