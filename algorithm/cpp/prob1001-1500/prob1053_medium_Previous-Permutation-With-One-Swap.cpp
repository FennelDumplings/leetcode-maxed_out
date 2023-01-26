// prob1053: Previous Permutation With One Swap

/*
 * https://leetcode-cn.com/problems/previous-permutation-with-one-swap/
 */

#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& A) {
        int n = A.size();
        if(n <= 1)
            return A;
        deque<int> deq;
        int ii = -1;
        for(int i = 1; i < n; ++i)
        {
            if(A[i] < A[i - 1])
                ii = i - 1;
        }
        if(ii == -1)
            return A;
        // [ii+1..n-1] 中寻找 A[j] < A[ii] 的最大的 A[j]
        int jj = ii + 1;
        for(int j = ii + 2; j < n; ++j)
        {
            if(A[j] < A[ii] && A[j] > A[jj])
                jj = j;
        }
        swap(A[ii], A[jj]);
        return A;
    }
};
