// prob989: Add to Array-Form of Integer

/*
 * https://leetcode-cn.com/problems/add-to-array-form-of-integer/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        int carry = 0;
        reverse(A.begin(), A.end());
        vector<int> result;
        int n = A.size();
        int i = 0;
        while(i < n || K > 0 || carry > 0)
        {
            int d = carry;
            if(K > 0)
            {
                d += K % 10;
                K /= 10;
            }
            if(i < n)
            {
                d += A[i];
                ++i;
            }
            carry = d / 10;
            result.push_back(d % 10);
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
