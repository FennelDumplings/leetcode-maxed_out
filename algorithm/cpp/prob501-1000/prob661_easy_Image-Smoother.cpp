// prob661: Image Smoother

/*
 * Given a 2D integer matrix M representing the gray scale of an image, you need to design a smoother to make the gray scale of each cell becomes the average gray scale (rounding down) of all the 8 surrounding cells and itself. If a cell has less than 8 surrounding cells, then use as many as you can.
 */

/*
 * Example 1:
 * Input:
 * [[1,1,1],
 *  [1,0,1],
 *  [1,1,1]]
 * Output:
 * [[0, 0, 0],
 *  [0, 0, 0],
 *  [0, 0, 0]]
 * Explanation:
 * For the point (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
 * For the point (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
 * For the point (1,1): floor(8/9) = floor(0.88888889) = 0
 */

/*
 * Note:
 * The value in the given matrix is in the range of [0, 255].
 * The length and width of the given matrix are in the range of [1, 150].
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int n = M.size(), m = M[0].size();
        if(n == 1 && m == 1) return M;
        vector<vector<int>> result(n, vector<int>(m, 0));
        if(n == 1)
        {
            for(int j = 0; j < m; ++j)
            {
                if(j == 0)
                    result[0][j] = (M[0][j] + M[0][j + 1]) / 2;
                else if(j == m - 1)
                    result[0][j] = (M[0][j] + M[0][j - 1]) / 2;
                else
                    result[0][j] = (M[0][j] + M[0][j + 1] + M[0][j - 1]) / 3;
            }
            return result;
        }
        if(m == 1)
        {
            for(int i = 0; i < n; ++i)
            {
                if(i == 0)
                    result[i][0] = (M[i][0] + M[i + 1][0]) / 2;
                else if(i == n - 1)
                    result[i][0] = (M[i][0] + M[i - 1][0]) / 2;
                else
                    result[i][0] = (M[i][0] + M[i - 1][0] + M[i + 1][0]) / 3;
            }
            return result;
        }
        vector<vector<int> > padding_row(1, vector<int>(m + 2));
        M.insert(M.begin(), padding_row.begin(), padding_row.end());
        M.insert(M.end(), padding_row.begin(), padding_row.end());
        vector<int> padding(1, 0);
        for(int i = 1; i < n + 1; ++i)
        {
            M[i].insert(M[i].begin(), padding.begin(), padding.end());
            M[i].insert(M[i].end(), padding.begin(), padding.end());
        }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int sum = cal(M, i, j);
                if((i == 0 && j == 0)|| (i == 0 && j == m - 1)
                        || (i == n - 1 && j == 0)|| (i == n - 1 && j == m - 1))
                    result[i][j] = (double)sum / 4;
                else if(i == 0 || i == n - 1 || j == 0 || j == m - 1)
                    result[i][j] = (double)sum / 6;
                else
                    result[i][j] = (double)sum / 9;
            }
        return result;
    }

private:
    int cal(vector<vector<int>>& M, int i, int j)
    {
        int result = 0;
        for(int x = i; x < i + 3; ++x)
            for(int y = j; y < j + 3; ++y)
            {
                result += M[x][y];
            }
        return result;
    }
};
