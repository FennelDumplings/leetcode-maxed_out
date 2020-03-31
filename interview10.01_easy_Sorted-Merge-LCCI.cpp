// interview10.01: Sorted Merge LCCI

/*
 * u are given two sorted arrays, A and B, where A has a large enough buffer at the end to hold B.
 * Write a method to merge B into A in sorted order.
 * Initially the number of elements in A and B are m and n respectively.
 */

/*
 * Example:
 * Input:
 * A = [1,2,3,0,0,0], m = 3
 * B = [2,5,6],       n = 3
 * Output: [1,2,2,3,5,6]
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        if(n <= 0) return;
        int iA = m - 1, iB = n - 1;
        for(int iter = m + n - 1; iter >= 0; --iter)
        {
            if(iA < 0)
            {
                A[iter] = B[iB];
                --iB;
                continue;
            }
            if(A[iA] >= B[iB])
            {
                A[iter] = A[iA];
                --iA;
            }
            else
            {
                A[iter] = B[iB];
                --iB;
                if(iB < 0)
                    break;
            }
        }
    }
};
