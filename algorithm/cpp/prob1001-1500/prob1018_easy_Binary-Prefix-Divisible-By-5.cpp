// prob1018: Binary Prefix Divisible By 5

/*
 * https://leetcode-cn.com/problems/binary-prefix-divisible-by-5/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& A) {
        if(A.empty()) return {};
        int n = A.size();
        vector<bool> result(n, false);
        int cur = 0;
        for(int i = 0; i < n; ++i)
        {
            int digit = A[i];
            cur *= 2;
            cur += digit;
            if(cur % 5 == 0)
                result[i] = true;
            cur = cur % 5;
        }
        return result;
    }
};
