// interview08.02: 八皇后

/*
 * https://leetcode-cn.com/problems/eight-queens-lcci/
 */

#include <string>
#include <vector>

using namespace std;

class Solution51 {
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

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        Solution51 solution;
        return solution.solveNQueens(n);
    }
};
