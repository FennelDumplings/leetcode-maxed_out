// prob795: Number of Subarrays with Bounded Maximum

/*
 * https://leetcode-cn.com/problems/number-of-subarrays-with-bounded-maximum/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& A, int L, int R) {
        int n = A.size();
        int left = 0;
        int ans = 0;
        while(left < n)
        {
            while(left < n && A[left] > R)
                ++left;
            if(left == n) break;
            int right = left;
            int last = -1;
            while(right < n && A[right] <= R)
            {
                if(A[right] >= L)
                {
                    ans += right - left + 1;
                    last = right;
                }
                else if(last != -1)
                    ans += last - left + 1;
                ++right;
            }
            left = right;
        }
        return ans;
    }
};
