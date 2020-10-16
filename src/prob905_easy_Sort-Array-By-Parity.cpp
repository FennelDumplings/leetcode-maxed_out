// prob905: Sort Array By Parity

/*
 * https://leetcode-cn.com/problems/sort-array-by-parity/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& A) {
        int n = A.size();
        int left = 0;
        int right = n - 1;
        while(left < right)
        {
            if(A[left] & 1)
                swap(A[left], A[right--]);
            else
                ++left;
        }
        return A;
    }
};
