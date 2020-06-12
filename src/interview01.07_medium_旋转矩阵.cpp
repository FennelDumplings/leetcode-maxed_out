// interview01.07: 旋转矩阵

/*
 * 给你一幅由 N × N 矩阵表示的图像，其中每个像素的大小为 4 字节。请你设计一种算法，将图像旋转 90 度。
 * 不占用额外内存空间能否做到？
 */

#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int i = 0; i <= (n - 1) / 2; ++i)
            for(int j = 0; j < n / 2; ++j)
                process(matrix, i, j);
    }

private:
    void process(vector<vector<int>>& matrix, int i, int j)
    {
        int n = matrix.size();
        int prev = matrix[i][j];
        for(int k = 0; k < 4; ++k)
        {
            int tmp = matrix[j][n - 1 - i];
            matrix[j][n - 1 - i] = prev;
            prev = tmp;
            int prev_j = j;
            j = n - 1 - i;
            i = prev_j;
        }
    }
};
