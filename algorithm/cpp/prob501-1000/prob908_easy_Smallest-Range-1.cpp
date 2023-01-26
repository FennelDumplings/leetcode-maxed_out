// prob908: Smallest Range I

/*
 * https://leetcode-cn.com/problems/smallest-range-i/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int smallestRangeI(vector<int>& A, int K) {
        int n = A.size();
        int l = 10001, h = -1;
        for(int i = 0; i < n; ++i)
        {
            l = min(l, A[i]);
            h = max(h, A[i]);
        }
        return max(h - l - 2 * K, 0);
    }
};
