// prob859: Buddy Strings

/*
 * https://leetcode-cn.com/problems/buddy-strings/
 */

#include <string>

using namespace std;

class Solution {
public:
    bool buddyStrings(string A, string B) {
        int n1 = A.size(), n2 = B.size();
        if(n1 != n2)
            return false;
        int j1 = -1, j2 = -1;
        int state = 0;
        bool flag = false;
        for(int i = 0; i < n1; ++i)
        {
            if(A[i] != B[i])
            {
                if(j1 == -1)
                    j1 = i;
                else if(j2 == -1)
                    j2 = i;
                else
                    return false;
            }
            if(state >> (A[i] - 'a') & 1)
                flag = true;
            state |= 1 << (A[i] - 'a');
        }
        if(j1 == -1)
            return flag;
        if(j2 == -1)
            return false;
        return A[j2] == B[j1] && A[j1] == B[j2];
    }
};
