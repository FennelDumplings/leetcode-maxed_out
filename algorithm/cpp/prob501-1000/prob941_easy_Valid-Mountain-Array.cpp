// prob941: Valid Mountain Array

/*
 * https://leetcode-cn.com/problems/valid-mountain-array/
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool validMountainArray(vector<int>& A) {
        int n = A.size();
        if(n < 3)
            return false;
        int l = 1, r = n - 2;
        while(l < n && A[l - 1] < A[l])
            ++l;
        while(r >= 0 && A[r] > A[r + 1])
            --r;
        return r >= 0 && l <= n - 1 && l - 1 == r + 1;
    }
};
