// prob51: N-Queens

/*
 * HardThe n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
 */

/*
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * Each solution contains a distinct board configuration of the n-queens' placement,
 * where 'Q' and '.' both indicate a queen and an empty space respectively.
 */

#include <vector>
#include <string>

using namespace std;

// 朴素 DFS
// 无剪枝，无位运算优化
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        if(n <= 0) return vector<vector<string>>();
        if(n == 1) return vector<vector<string>>(1, vector<string>(1,"Q"));

        vector<vector<string> > result;
        vector<string> board(n, string(n, '.'));
        dfs(result, 0, board, n);
        return result;
    }

private:
    void dfs(vector<vector<string> >& result, int row, vector<string>& board, int n)
    {
        // 退出条件
        if(row == n)
        {
            result.push_back(board);
            return;
        }

        for(int j = 0; j < n; ++j)
        {
            if(board[row][j] == '.')
            {
                if(check(board, row, j))
                {
                    board[row][j] = 'Q';
                    dfs(result, row + 1, board, n);
                    board[row][j] = '.';
                }
            }
        }
    }

    bool check(vector<string>& board, int x, int y)
    {
        int n = board.size();
        for(int j = 0; j < n; ++j)
        {
            if(board[x][j] == 'Q')
                return false;
        }
        for(int i = 0; i < n; ++i)
        {
            if(board[i][y] == 'Q')
                return false;
        }
        for(int i = x, j = y; i < n && j < n; ++i, ++j)
        {
            if(board[i][j] == 'Q')
                return false;
        }
        for(int i = x, j = y; i >= 0 && j < n; --i, ++j)
        {
            if(board[i][j] == 'Q')
                return false;
        }
        for(int i = x, j = y; i < n && j >= 0; ++i, --j)
        {
            if(board[i][j] == 'Q')
                return false;
        }
        for(int i = x, j = y; i >= 0 && j >= 0; --i, --j)
        {
            if(board[i][j] == 'Q')
                return false;
        }
        return true;
    }
};
