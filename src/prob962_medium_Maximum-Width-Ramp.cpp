// prob962: Maximum Width Ramp

/*
 * Given an array A of integers, a ramp is a tuple (i, j) for which i < j and A[i] <= A[j].  The width of such a ramp is j - i.
 * Find the maximum width of a ramp in A.  If one doesn't exist, return 0.
 */

/*
 * Example 1:
 * Input: [6,0,8,2,1,5]
 * Output: 4
 * Explanation:
 * The maximum width ramp is achieved at (i, j) = (1, 5): A[1] = 0 and A[5] = 5.
 * Example 2:
 * Input: [9,8,1,0,1,9,4,0,4,1]
 * Output: 7
 * Explanation:
 * The maximum width ramp is achieved at (i, j) = (2, 9): A[2] = 1 and A[9] = 1.
 */

/*
 * Note:
 * 2 <= A.length <= 50000
 * 0 <= A[i] <= 50000
 */

#include <vector>

using namespace std;


class Solution {
public:
    int maxWidthRamp(vector<int>& A) {
        if(A.empty()) return 0;
        int n = A.size();
        vector<int> veci, vecj;
        veci.push_back(0);
        int cur = A[0];
        for(int i = 1; i < n; ++i)
        {
            if(A[i] < cur)
            {
                veci.push_back(i);
                cur = A[i];
            }
        }
        vecj.push_back(n - 1);
        cur = A[n - 1];
        for(int j = n - 2; j >= 0; --j)
        {
            if(A[j] > cur)
            {
                vecj.push_back(j);
                cur = A[j];
            }
        }
        int ni = veci.size(), nj = vecj.size();
        int j = 0;
        int result = 0;
        for(int i = ni - 1; i >= 0; --i)
        {
            while(j < nj && A[vecj[j]] < A[veci[i]])
                ++j;
            if(j < nj)
                result = max(result, vecj[j] - veci[i]);
        }
        return result;
    }
};
