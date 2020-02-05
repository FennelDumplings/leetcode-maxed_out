// Prob54: spiral matrix

/*Description
 * Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.
*/

/*
 *Example 1:
 * Input:
 * [
 *  [ 1, 2, 3 ],
 *  [ 4, 5, 6 ],
 *  [ 7, 8, 9 ]
 * ]
 * Output: [1,2,3,6,9,8,7,4,5]
 * Example 2:
 * Input:
 * [
 *   [1, 2, 3, 4],
 *   [5, 6, 7, 8],
 *   [9,10,11,12]
 * ]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 */

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 特判
        int m = matrix.size();
        if(m == 0) return vector<int>();
        return _spiralOrder(matrix, 0, 0);
    }

private:
    vector<int> _spiralOrder(vector<vector<int>>& matrix, int lt_m, int lt_n)
    {
        // 进入此函数，说明 matrix 不为空
        // lt_m,lt_n 是当前考虑的子矩阵左上角的行号和列号
        // m 和 n 是当前考虑的子矩阵的行数和列数
        int m = matrix.size() - 2 * lt_m;
        int n = matrix[0].size() - 2 * lt_n;
        vector<int> result;
        while(m > 0 && n > 0)
        {
            // 当前考虑的子矩阵至少是一行一列
            if(m == 1)
                for(int j = lt_n; j < lt_n + n; ++j)
                    result.push_back(matrix[lt_m][j]);
            else if(n == 1)
                for(int i = lt_m; i < lt_m + m; ++i)
                    result.push_back(matrix[i][lt_n]);
            else
            {
                // 当前考虑的子矩阵至少是两行两列: m >= 2, n >= 2
                // left2right
                for(int j = lt_n; j < lt_n + n; ++j)
                    result.push_back(matrix[lt_m][j]);
                // top2down
                for(int i = lt_m + 1; i < lt_m + m; ++i)
                    result.push_back(matrix[i][lt_n + n - 1]);
                // right2left: n - 2 * lt_n - 2 -> 0 (只有两列的话是 0 -> 0)
                for(int j = lt_n + n - 2; j >= lt_n; --j)
                    result.push_back(matrix[lt_m + m - 1][j]);
                // donw2top: m - 2 * lt_m - 2 -> 1 (m = 2 的时候: 0 -> 1, 没有，此情况循环条件不成立)
                for(int i = lt_m + m - 2; i >= lt_m + 1; --i)
                    result.push_back(matrix[i][lt_n]);
            }
            // 当前考虑的子矩阵一圈遍历完了，接下来递归地遍历下一个圈
            ++lt_m;
            ++lt_n;
            m = matrix.size() - 2 * lt_m;
            n = matrix[0].size() - 2 * lt_n;
        }
        return result;
    }
};

// dx = {0, 1, 0, -1}
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        // 特判
        int m = matrix.size();
        if(m == 0) return vector<int>();
        return _spiralOrder(matrix, 0, 0);
    }
}

int main()
{
    int M, N;
    cin >> M >> N;
    vector<vector<int> > input(M, vector<int>(N, 0));
    for(int i = 0; i < M; ++i)
        for( int j = 0; j < N; ++j)
            cin >> input[i][j];

    Solution solution;
    vector<int> result = solution.spiralOrder(input);

    for(int item: result)
        cout << item << " ";
    cout << endl;
}
