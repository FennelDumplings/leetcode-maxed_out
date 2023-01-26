// prob348: Design Tic-Tac-Toe

/*
 * Design a Tic-tac-toe game that is played between two players on a n x n grid.
 * You may assume the following rules:
 * A move is guaranteed to be valid and is placed on an empty block.
 * Once a winning condition is reached, no more moves is allowed.
 * A player who succeeds in placing n of their marks in a horizontal, vertical, or diagonal row wins the game.
 */

#include <vector>

using namespace std;

class TicTacToe {
public:
    /** Initialize your data structure here. */
    TicTacToe(int n) {
        state = vector<vector<char> >(n, vector<char>(n, ' '));
    }

    /** Player {player} makes a move at ({row}, {col}).
        @param row The row of the board.
        @param col The column of the board.
        @param player The player, can be either 1 or 2.
        @return The current winning condition, can be either:
                0: No one wins.
                1: Player 1 wins.
                2: Player 2 wins. */
    int move(int row, int col, int player) {
        // 1 -> X
        // 2 -> O
        if(player == 1)
        {
            state[row][col] = 'X';
            if(_check(row, col, 'X'))
                return 1;
            else
                return 0;
        }
        else
        {
            state[row][col] = 'O';
            if(_check(row, col, 'O'))
                return 2;
            else
                return 0;
        }
    }

private:
    vector<vector<char> > state;

    bool _check(int row, int col, char cur)
    {
        int n = state.size();
        bool flag_col = true;
        for(int j = 0; j < n; ++j)
        {
            if(state[row][j] != cur)
            {
                flag_col = false;
                break;
            }
        }
        if(flag_col) return true;
        bool flag_row = true;
        for(int i = 0; i < n; ++i)
        {
            if(state[i][col] != cur)
            {
                flag_row = false;
                break;
            }
        }
        if(flag_row) return true;
        if(row == col)
        {
            bool flag_diag1 = true;
            for(int i = 0; i < n; ++i)
            {
                if(state[i][i] != cur)
                {
                    flag_diag1 = false;
                    break;
                }
            }
            if(flag_diag1) return true;
        }
        if(row + col == n - 1)
        {
            bool flag_diag2 = true;
            for(int i = 0; i < n; ++i)
            {
                if(state[i][n - 1 - i] != cur)
                {
                    flag_diag2 = false;
                    break;
                }
            }
            if(flag_diag2) return true;
        }
        return false;
    }
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */
