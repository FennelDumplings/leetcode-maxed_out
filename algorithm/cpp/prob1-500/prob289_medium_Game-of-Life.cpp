// prob289: Game of Life

/*
 * According to the Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by
 * the British mathematician John Horton Conway in 1970."
 * Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight
 * neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):
 * Any live cell with fewer than two live neighbors dies, as if caused by under-population.
 * Any live cell with two or three live neighbors lives on to the next generation.
 * Any live cell with more than three live neighbors dies, as if by over-population..
 * Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 * Write a function to compute the next state (after one update) of the board given its current state. 
 * The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously.
 */

/*
 * Example:
 * Input:
 * [
 *   [0,1,0],
 *   [0,0,1],
 *   [1,1,1],
 *   [0,0,0]
 * ]
 * Output:
 * [
 *   [0,0,0],
 *   [1,0,1],
 *   [0,1,1],
 *   [0,1,0]
 * ]
 */

/*
 * Follow up:
 * Could you solve it in-place? Remember that the board needs to be updated at the same time: You
 * cannot update some cells first and then use their updated values to update other cells.
 * In this question, we represent the board using a 2D array. In principle, the board is infinite,
 * which would cause problems when the active area encroaches the border of the array. How would you address these problems?
 */

#include <vector>

using namespace std;

// 开额外网格
class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<int> > tmp(board.begin(), board.end());
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int cnt = _check(tmp, i, j);
                if(cnt < 2 || cnt > 3)
                    board[i][j] = 0;
                if(cnt == 3)
                    board[i][j] = 1;
            }
    }

private:
    int _check(vector<vector<int> >& board, int i, int j)
    {
        int n = board.size(), m = board[0].size();
        int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
        int dy[8] = {1, -1, -1, 0, 1, -1, 0, 1};
        int cnt = 0;
        for(int d = 0; d < 8; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m) continue;
            cnt += board[x][y];
        }
        return cnt;
    }
};

// 因状态只有 0, 1
// 可以用 int 的第二位保存
class Solution_2 {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int n = board.size(), m = board[0].size();
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
            {
                int cnt = _check(board, i, j);
                if(cnt == 3)
                    board[i][j] |= (1 << 1);
                if(cnt == 2 && (board[i][j] & 1) == 1)
                    board[i][j] |= (1 << 1);
            }
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                board[i][j] >>= 1;
    }

private:
    int _check(vector<vector<int> >& board, int i, int j)
    {
        int n = board.size(), m = board[0].size();
        int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
        int dy[8] = {1, -1, -1, 0, 1, -1, 0, 1};
        int cnt = 0;
        for(int d = 0; d < 8; ++d)
        {
            int x = i + dx[d];
            int y = j + dy[d];
            if(x < 0 || x >= n || y < 0 || y >= m) continue;
            cnt += board[x][y] & 1;
        }
        return cnt;
    }
};

// 卷积
class Solution_3 {
public:
    void gameOfLife(vector<vector<int>>& board) {
        Mat kernel(3, vector<int>(3, 1));
        kernel[1][1] = 0;
        int n = board.size(), m = board[0].size();
        Mat input_padding(n + 2, vector<int>(m + 2, 0));
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                input_padding[i][j] = board[i - 1][j - 1];
        _conv2(input_padding, kernel, board);
    }

private:
    using Mat = vector<vector<int> >;

    void _conv2(Mat& input, Mat& kernel, Mat& output)
    {
        int n = input.size(), m = input[0].size();
        //计算卷积核的半径
        int kn = kernel.size(), km = kernel.size();
        int sub_x = kn / 2;
        int sub_y = km / 2;
        for(int j = 0; j < m - 2 * sub_y; ++j)
            for(int i = 0; i < n - 2 * sub_x; ++i)
            {
                int cnt = 0;
                for(int kernel_i = 0; kernel_i < kn; ++kernel_i)
                    for(int kernel_j = 0; kernel_j < km; ++kernel_j)
                    {
                        int weight = kernel[kernel_i][kernel_j];
                        int pixel = input[i + kernel_i][j + kernel_j];
                        cnt += weight * pixel;
                    }
                if(cnt == 3 && output[i][j] == 0)
                    output[i][j] = 1;
                if(cnt < 2 || cnt > 3)
                    output[i][j] = 0;
            }
    }
};
