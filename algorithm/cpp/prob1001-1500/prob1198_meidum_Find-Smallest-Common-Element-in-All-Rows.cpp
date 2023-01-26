// prob1198: Find Smallest Common Element in All Rows

/*
 * https://leetcode-cn.com/problems/find-smallest-common-element-in-all-rows/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int smallestCommonElement(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        for(int j = 0; j < m; ++j)
        {
            int cur = mat[0][j];
            for(int i = 1; i < n; ++i)
                cur = max(cur, mat[i][j]);
            if(check(mat, cur))
                return cur;
        }
        return -1;
    }

private:
    bool check(vector<vector<int>>& mat, int cur)
    {
        int n = mat.size();
        for(int i = 0; i < n; ++i)
        {
            auto it = lower_bound(mat[i].begin(), mat[i].end(), cur);
            if(*it != cur)
                return false;
        }
        return true;
    }
};
