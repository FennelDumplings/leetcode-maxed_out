// prob861: Score After Flipping Matrix

/*
 * https://leetcode-cn.com/problems/score-after-flipping-matrix/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int matrixScore(vector<vector<int>>& A) {
        int n = A.size(), m = A[0].size();
        for(vector<int>& row: A)
        {
            if(row[0] == 0)
                for(int &j: row)
                    j ^= 1;
        }
        vector<int> p2(m, 1);
        for(int i = 1; i < m; ++i)
            p2[i] = p2[i - 1] * 2;
        for(int j = 1; j < m; ++j)
        {
            int cnt0 = 0, cnt1 = 0;
            for(int i = 0; i < n; ++i)
            {
                if(A[i][j] == 0)
                    ++cnt0;
                else
                    ++cnt1;
            }
            if(cnt1 < cnt0)
            {
                for(int i = 0; i < n; ++i)
                    A[i][j] ^= 1;
            }
        }
        int ans = 0;
        for(int j = 0; j < m; ++j)
        {
            int cnt1 = 0;
            for(int i = 0; i < n; ++i)
                cnt1 += A[i][j];
            ans += cnt1 * p2[m - j - 1];
        }
        return ans;
    }
};
