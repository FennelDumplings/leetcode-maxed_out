// prob794: Valid Tic-Tac-Toe State

/*
 * A Tic-Tac-Toe board is given as a string array board. Return True if and only if it is possible to reach this
 * board position during the course of a valid tic-tac-toe game.
 * The board is a 3 x 3 array, and consists of characters " ", "X", and "O".  The " " character represents an empty square.
 * Here are the rules of Tic-Tac-Toe:
 * Players take turns placing characters into empty squares (" ").
 * The first player always places "X" characters, while the second player always places "O" characters.
 * "X" and "O" characters are always placed into empty squares, never filled ones.
 * The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
 * The game also ends if all squares are non-empty.
 * No more moves can be played if the game is over.
 */

/*
 * Example 1:
 * Input: board = ["O  ", "   ", "   "]
 * Output: false
 * Explanation: The first player always plays "X".
 * Example 2:
 * Input: board = ["XOX", " X ", "   "]
 * Output: false
 * Explanation: Players take turns making moves.
 * Example 3:
 * Input: board = ["XXX", "   ", "OOO"]
 * Output: false
 * Example 4:
 * Input: board = ["XOX", "O O", "XOX"]
 * Output: true
 */

/*
 * Note:
 * board is a length-3 array of strings, where each string board[i] has length 3.
 * Each board[i][j] is a character in the set {" ", "X", "O"}.
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int cnt_o = 0, cnt_x = 0;
        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
            {
                if(board[i][j] == 'X')
                    ++cnt_x;
                if(board[i][j] == 'O')
                    ++cnt_o;
            }
        if(cnt_o != cnt_x && cnt_o + 1 != cnt_x)
            return false;
        if(cnt_o == cnt_x && cnt_o == 0)
            return true;
        if(_check3(board)) return true;
        if(cnt_o == cnt_x)
        {
            for(int i = 0; i < 3; ++i)
                for(int j = 0; j < 3; ++j)
                {
                    if(board[i][j] == 'O')
                    {
                        board[i][j] = ' ';
                        if(_check3(board))
                            return true;
                        board[i][j] = 'O';
                    }
                }
            return false;
        }
        else
        {
            for(int i = 0; i < 3; ++i)
                for(int j = 0; j < 3; ++j)
                {
                    if(board[i][j] == 'X')
                    {
                        board[i][j] = ' ';
                        if(_check3(board))
                            return true;
                        board[i][j] = 'X';
                    }
                }
            return false;
        }
    }

private:
    bool _check3(const vector<string>& board)
    {
        // 没有3连就返回true
        for(int i = 0; i < 3; ++i)
        {
            if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
                return false;
            if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
                return false;
        }
        if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
            return false;
        if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
            return false;
        return true;
    }
};
