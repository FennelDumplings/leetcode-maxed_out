// 20200613
// 2. 子矩形查询

/*
 * 请你实现一个类 SubrectangleQueries ，它的构造函数中接收 rows x cols 的整数矩阵，并支持以下两种操作：
 *
 * 1. updateSubrectangle(int row1, int col1, int row2, int col2, int newValue)
 *
 * 用 newValue 更新以 (row1,col1) 为左上角且以 (row2,col2) 为右下角的子矩形。
 * 2. getValue(int row, int col)
 *
 * 返回矩形中坐标为 (row,col) 当前的值。
 */

#include <vector>

using namespace std;

class SubrectangleQueries {
public:
    SubrectangleQueries(vector<vector<int>>& rectangle) {
        vec = vector<vector<int>>(rectangle.begin(), rectangle.end());
    }

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        for(int i = row1; i <= row2; ++i)
            for(int j = col1; j <= col2; ++j)
            {
                vec[i][j] = newValue;
            }
    }

    int getValue(int row, int col) {
        return vec[row][col];
    }

private:
    vector<vector<int>> vec;
};
