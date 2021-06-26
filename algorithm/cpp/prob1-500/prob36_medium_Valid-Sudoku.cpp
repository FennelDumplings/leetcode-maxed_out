// prob36: Valid Sudoku

/*
 * Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
 * Each row must contain the digits 1-9 without repetition.
 * Each column must contain the digits 1-9 without repetition.
 * Each of the 9 3x3 sub-boxes of the grid must contain the digits 1-9 without repetition.
 */

#include <vector>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool> > row_state(9, vector<bool>(9, false));
        vector<vector<bool> > col_state(9, vector<bool>(9, false));
        vector<vector<bool> > block_state(9, vector<bool>(9, false));
        for(int i = 0; i < 9; ++i)
            for(int j = 0; j < 9; ++j)
            {
                if(board[i][j] != '.')
                {
                    if(!row_state[i][int(board[i][j] - '0' - 1)])
                        row_state[i][int(board[i][j] - '0' - 1)] = true;
                    else
                        return false;
                    if(!col_state[j][int(board[i][j] - '0' - 1)])
                        col_state[j][int(board[i][j] - '0' - 1)] = true;
                    else
                        return false;
                    if(!block_state[_get_block_id(i, j)][int(board[i][j] - '0' - 1)])
                        block_state[_get_block_id(i, j)][int(board[i][j] - '0' - 1)] = true;
                    else
                        return false;
                }
            }
        return true;
    }

private:
    int _get_block_id(int i, int j)
    {
        if(i <= 2)
        {
            if(j <= 2)
                return 0;
            else if(j >= 3 && j <= 5)
                return 1;
            else
                return 2;
        }
        else if(i >= 3 && i <= 5)
        {
            if(j <= 2)
                return 3;
            else if(j >= 3 && j <= 5)
                return 4;
            else
                return 5;
        }
        else
        {
            if(j <= 2)
                return 6;
            else if(j >= 3 && j <= 5)
                return 7;
            else
                return 8;
        }
    }
};
