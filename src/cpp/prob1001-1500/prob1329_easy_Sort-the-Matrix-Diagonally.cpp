// prob1329: Sort the Matrix Diagonally

/*
 * https://leetcode-cn.com/problems/sort-the-matrix-diagonally/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat.size();
        vector<int> cand;
        vector<vector<int>> result(n, vector<int>(m, -1));
        for(int k = -(n - 1); k <= m - 1; ++k)
        {
            // k = j - i
            cand.clear();
            for(int i = min(0, -k); i <= min(n - 1, m - 1 - k); ++i)
            {
                int j = i + k;
                cand.push_back(mat[i][j]);
            }
            sort(cand.begin(), cand.end());
            int iter = 0;
            for(int i = min(0, -k); i <= min(n - 1, m - 1 - k); ++i)
            {
                int j = i + k;
                result[i][j] = cand[iter++];
            }
        }
        return result;
    }
};
