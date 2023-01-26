// prob995: Minimum Number of K Consecutive Bit Flips

/*
 * https://leetcode-cn.com/problems/minimum-number-of-k-consecutive-bit-flips/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int minKBitFlips(vector<int>& A, int K) {
        int n = A.size();
        if(n < K)
            return -1;
        int ans = 0;
        int flip = 0;
        vector<int> events(n, 0);
        for(int l = 0; l < n; ++l)
        {
            if((A[l] ^ flip) == 0)
            {
                if(l + K - 1 >= n)
                    return -1;
                flip ^= 1;
                events[l + K - 1] = 1;
                ++ans;
            }
            flip ^= events[l];
        }
        return ans;
    }
};
