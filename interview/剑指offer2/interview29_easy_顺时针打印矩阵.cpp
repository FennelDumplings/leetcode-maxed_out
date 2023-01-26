// interview29: 顺时针打印矩阵

/*
 * https://leetcode-cn.com/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.empty()) return vector<int>();
        // dx, dy 的模板写法
        int m = matrix.size();
        int n = matrix[0].size();
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int x = 0, y = 0, d = 0; // 初始位置 (0, 0), 初始方向(0, 1)
        vector<vector<bool> > watched(m, vector<bool>(n, false));
        vector<int> result;
        for(int i = 0; i < m * n; ++i)
        {
            // 一共输出 m * n 个数, 所以做 m * n 次循环
            // 先判断下一步要不要改方向
            // 按照原方向，下一个位置点
            int x_next = x + dx[d];
            int y_next = y + dy[d];
            if(x_next == m || y_next == n || x_next < 0 || y_next < 0 || watched[x_next][y_next])
            {
                // (x + dx, y + dy) 越界或者此前已经遍历过，则换方向
                d = (d + 1) % 4;
            }
            result.push_back(matrix[x][y]);
            watched[x][y] = true; // (x, y) 已经遍历过
            x += dx[d];
            y += dy[d];
        }
        return result;
    }
};
