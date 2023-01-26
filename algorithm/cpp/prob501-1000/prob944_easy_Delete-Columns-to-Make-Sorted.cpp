// prob944: Delete Columns to Make Sorted

/*
 * https://leetcode-cn.com/problems/delete-columns-to-make-sorted/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int n = A.size(), m = A[0].size();
        if(n == 1) return {};
        int ans = 0;
        for(int j = 0; j < m; ++j)
            if(!check(j, A))
                ++ans;
        return ans;
    }

private:
    bool check(int j, const vector<string>& A)
    {
        int n = A.size();
        for(int i = 1; i < n; ++i)
        {
            if(A[i][j] < A[i - 1][j])
                return false;
        }
        return true;
    }
};
