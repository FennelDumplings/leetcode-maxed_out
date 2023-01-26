// prob910: Smallest Range II

/*
 * https://leetcode-cn.com/problems/smallest-range-ii/
 */

#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int n = A.size();
        int d = A[n - 1] - A[0]; // 全 + 的极差
        for(int i = 0; i < n - 1; ++i)
        {
            // [0..i] +K, [i+1..n-1] -K
            int min_l = min(A[i + 1] - K, A[0] + K);
            int max_h = max(A[i] + K, A[n - 1] - K);
            d = min(d, max_h - min_l);
        }
        return d;
    }
};
