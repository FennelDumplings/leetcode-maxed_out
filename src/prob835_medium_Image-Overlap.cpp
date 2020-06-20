// prob835: Image Overlap

/*
 * Two images A and B are given, represented as binary, square matrices of the same size.  (A binary matrix has only 0s and 1s as values.)
 * We translate one image however we choose (sliding it left, right, up, or down any number of units), and place it on top of the other image.  After, the overlap of this translation is the number of positions that have a 1 in both images.
 * (Note also that a translation does not include any kind of rotation.)
 * What is the largest possible overlap?
 */

/*
 * Example 1:
 * Input: A = [[1,1,0],
 *             [0,1,0],
 *             [0,1,0]]
 *        B = [[0,0,0],
 *             [0,1,1],
 *             [0,0,1]]
 * Output: 3
 * Explanation: We slide A to right by 1 unit and down by 1 unit.
 */

/*
 * Notes: 
 * 1 <= A.length = A[0].length = B.length = B[0].length <= 30
 * 0 <= A[i][j], B[i][j] <= 1
 */

#include <vector>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size(), n = A[0].size();
        // B 的上下各补上 m - 1 行
        vector<vector<int> > to_te_inserted(m - 1, vector<int>((n - 1) * 2 + n));
        B.insert(B.begin(), to_te_inserted.begin(), to_te_inserted.end());
        B.insert(B.end(), to_te_inserted.begin(), to_te_inserted.end());
        vector<int> padding(n - 1);
        for(int i = m - 1; i < (m - 1 + m); ++i)
        {
            B[i].insert(B[i].begin(), padding.begin(), padding.end());
            B[i].insert(B[i].end(), padding.begin(), padding.end());
        }
        int result = 0;
        for(int i = 0; i < m * 2 - 1; ++i)
        {
            for(int j = 0; j < n * 2 - 1; ++j)
            {
                int cnt = check(A, B, i, j);
                result = max(result, cnt);
            }
        }
        return result;
    }

private:
    int check(vector<vector<int>>& A, vector<vector<int>>& B, int i, int j)
    {
        int m = A.size(), n = A[0].size();
        int result = 0;
        for(int x = i; x < i + m; ++x)
            for(int y = j; y < j + n; ++y)
            {
                if(A[x - i][y - j] == 1 && B[x][y] == 1)
                    ++result;
            }
        return result;
    }
};
