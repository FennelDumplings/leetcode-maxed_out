// prob52: N-Queens 2

/*
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
 * Given an integer n, return the number of distinct solutions to the n-queens puzzle.
 */

#include <vector>
#include <string>

using namespace std;

// 朴素 DFS，不带剪枝和位运算
// 答案通过在参数中引用维护
class Solution {
public:
    int totalNQueens(int n) {
        if(n <= 0) return 0;
        if(n == 1) return 1;

        int result = 0;
        vector<string> board(n, string(n, '.'));
        dfs(result, 0, board, n);
        return result;
    }

private:
    void dfs(int& result, int row, vector<string>& board, int n)
    {
        if(row == n)
        {
            ++result;
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

// 答案通过返回值返回
// 简单剪枝，第一行只走一半
class Solution_2 {
public:
    int totalNQueens(int n) {
        if(n <= 0) return 0;
        if(n == 1) return 1;

        vector<string> board(n, string(n, '.'));
        int result = dfs(0, board, n);
        return result;
    }

private:
    int dfs(int row, vector<string>& board, int n)
    {
        if(row == n)
        {
            return 1;
        }

        int result = 0;
        if(row == 0)
        {
            for(int j = 0; j < n / 2; ++j)
            {
                if(board[row][j] == '.')
                {
                    if(check(board, row, j))
                    {
                        board[row][j] = 'Q';
                        result += dfs(row + 1, board, n);
                        board[row][j] = '.';
                    }
                }
            }
            result *= 2;
            if(n % 2 == 1)
            {
                board[row][n / 2] = 'Q';
                result += dfs(row + 1, board, n);
                board[row][n / 2] = '.';
            }
        }
        else
        {
            for(int j = 0; j < n; ++j)
            {
                if(board[row][j] == '.')
                {
                    if(check(board, row, j))
                    {
                        board[row][j] = 'Q';
                        result += dfs(row + 1, board, n);
                        board[row][j] = '.';
                    }
                }
            }
        }
        return result;
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

// 状态压缩
class Solution_3 {
public:
    int totalNQueens(int n) {
        if(n <= 0) return 0;
        if(n == 1) return 1;

        int result = 0;
        dfs(0, 0, 0, 0, n, result);
        return result;
    }

private:
    void dfs(int dep, int r, int s1, int s2, int n, int& cnt)
    {
        if(dep == n)
        {
            ++cnt;
            return;
        }

        for(int i = 0; i < n; ++i)
        {
            int j = 1 << i;
            if((j & r) || (j & s1) || (j & s2)) continue;
            dfs(dep + 1, (j | r), (j | s1) << 1, (j | s2) >> 1, n, cnt);
        }
    }
};
