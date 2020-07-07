// prob955: Delete Columns to Make Sorted II

/*
 * https://leetcode-cn.com/problems/delete-columns-to-make-sorted-ii/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minDeletionSize(vector<string>& A) {
        int n = A.size(), m = A[0].size();
        if(n == 1) return 0;
        int ans = 0;
        vector<bool> rows(n, true);
        rows[0] = false;
        int n_rows = n - 1;
        for(int j = 0; j < m; ++j)
        {
            if(!check(j, A, rows, n_rows))
                ++ans;
            else if(n_rows == 0)
                return ans;
        }
        return ans;
    }

private:
    bool check(int j, const vector<string>& A, vector<bool>& rows, int& n_rows)
    {
        int n = A.size();
        vector<int> tmp;
        for(int i = 0; i < n; ++i)
        {
            if(!rows[i]) continue;
            if(A[i - 1][j] > A[i][j])
                return false;
            if(A[i - 1][j] < A[i][j])
            {
                tmp.push_back(i);
            }
        }
        for(int i: tmp)
        {
            --n_rows;
            rows[i] = false;
        }
        return true;
    }
};
