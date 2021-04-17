// prob922: Sort Array By Parity II

/*
 * https://leetcode-cn.com/problems/sort-array-by-parity-ii/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int n = A.size();
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(A[left] & 1)
                swap(A[left], A[right--]);
            else
                ++left;
        }
        vector<int> result(n, -1);
        for(int i = 0; i < n / 2; ++i)
        {
            result[i * 2] = A[i];
            result[i * 2 + 1] = A[i + n / 2];
        }
        return result;
    }
};
