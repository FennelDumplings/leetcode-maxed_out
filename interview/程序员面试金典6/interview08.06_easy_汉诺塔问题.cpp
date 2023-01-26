// interview08.06: 汉诺塔问题

/*
 * https://leetcode-cn.com/problems/hanota-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        int n = A.size();
        hanota(A, B, C, n);
    }

private:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C, int n)
    {
        if(n == 1)
        {
            C.push_back(A.back());
            A.pop_back();
            return;
        }
        hanota(A, C, B, n - 1);
        hanota(A, B, C, 1);
        hanota(B, A, C, n - 1);
    }
};
