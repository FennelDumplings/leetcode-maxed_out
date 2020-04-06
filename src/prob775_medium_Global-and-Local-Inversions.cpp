// prob: Global and Local Inversions

/*
 * We have some permutation A of [0, 1, ..., N - 1], where N is the length of A.
 * The number of (global) inversions is the number of i < j with 0 <= i < j < N and A[i] > A[j].
 * The number of local inversions is the number of i with 0 <= i < N and A[i] > A[i+1].
 * Return true if and only if the number of global inversions is equal to the number of local inversions.
 */

/*
 *
 * Example 1:
 * Input: A = [1,0,2]
 * Output: true
 * Explanation: There is 1 global inversion, and 1 local inversion.
 * Example 2:
 * Input: A = [1,2,0]
 * Output: false
 * Explanation: There are 2 global inversions, and 1 local inversion.
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isIdealPermutation(vector<int>& A) {
        int n = A.size();
        if(n <= 2) return true;
        int maxx = A[0];
        int prev = A[1];
        for(int i = 2; i < n; ++i)
        {
            if(A[i] < maxx) return false;
            maxx = max(maxx, prev);
            prev = A[i];
        }
        return true;
    }
};


// |A[i] - i| <= 1
class Solution_2 {
public:
    bool isIdealPermutation(vector<int>& A) {
        int n = A.size();
        if(n <= 2) return true;
        for(int i = 0; i < n; ++i)
        {
            if(abs(A[i] - i) > 1)
                return false;
        }
        return true;
    }
};
