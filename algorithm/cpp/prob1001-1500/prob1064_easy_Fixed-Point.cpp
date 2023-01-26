// prob1064: Fixed Point

/*
 * https://leetcode-cn.com/problems/fixed-point/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int fixedPoint(vector<int>& A) {
        int n = A.size();
        int left = 0, right = n - 1;
        while(left < right)
        {
            int mid = (left + right) / 2;
            if(A[mid] < mid)
                left = mid + 1;
            else
                right = mid;
        }
        if(A[left] == left)
            return left;
        return -1;
    }
};
