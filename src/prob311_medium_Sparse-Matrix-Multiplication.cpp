// prob311: Sparse Matrix Multiplication

/*
 * Given two sparse matrices A and B, return the result of AB.
 * You may assume that A's column number is equal to B's row number.
 */

/*
 * Example:
 * Input:
 * A = [
 *   [ 1, 0, 0],
 *   [-1, 0, 3]
 * ]
 * B = [
 *   [ 7, 0, 0 ],
 *   [ 0, 0, 0 ],
 *   [ 0, 0, 1 ]
 * ]
 * Output:
 *      |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
 * AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
 *                   | 0 0 1 |
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        if(A.empty()) return {};
        int ni = A.size(), nk = B.size(), nj = B[0].size();
        vector<vector<int>> result(ni, vector<int>(nj, 0));
        vector<unordered_map<int, int>> a(ni), b(nj);
        for(int i = 0; i < ni; ++i)
            for(int k = 0; k < nk; ++k)
            {
                if(A[i][k] != 0)
                    a[i][k] = A[i][k];
            }
        for(int k = 0; k < nk; ++k)
            for(int j = 0; j < nj; ++j)
            {
                if(B[k][j] != 0)
                    b[j][k] = B[k][j];
            }
        for(int i = 0; i < ni; ++i)
            for(int j = 0; j < nj; ++j)
            {
                int cij = 0;
                for(PII item: a[i])
                {
                    int k = item.first;
                    if(b[j].find(k) != b[j].end())
                        cij += item.second * b[j][k];
                }
                result[i][j] = cij;
            }
        return result;
    }

private:
    using PII = pair<int, int>;
};
