// prob999: Available Captures for Rook

/*
 * On an 8 x 8 chessboard, there is one white rook.  There also may be empty squares, white bishops, and black pawns. 
 * These are given as characters 'R', '.', 'B', and 'p' respectively. Uppercase characters represent white pieces,
 * and lowercase characters represent black pieces.
 * The rook moves as in the rules of Chess: it chooses one of four cardinal directions (north, east, west, and south),
 * then moves in that direction until it chooses to stop, reaches the edge of the board, or captures an opposite
 * colored pawn by moving to the same square it occupies.  Also, rooks cannot move into the same square as other friendly bishops.
 * Return the number of pawns the rook can capture in one move.
 */

/*
 * Note:
 * board.length == board[i].length == 8
 * board[i][j] is either 'R', '.', 'B', or 'p'
 * There is exactly one cell with board[i][j] == 'R'
 */

#include <vector>

using namespace std;

class Solution {
public:
    int numRookCaptures(vector<vector<char>>& board) {
        // 找车位置
        int x = 0, y = 0;
        for(int i = 0; i < 8; ++i)
            for(int j = 0; j < 8; ++j)
                if(board[i][j] == 'R')
                {
                    x = i;
                    y = j;
                    break;
                }

        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, 1, 0, -1};
        int result = 0;
        for(int d = 0; d < 4; ++d)
        {
            if(_check(board, x, y, dx[d], dy[d]))
                ++result;
        }
        return result;
    }

private:
    bool _check(vector<vector<char> >& board, int x, int y, int dx, int dy)
    {
        while(x >= 0 && x <= 7 && y >= 0 && y <= 7 && (board[x][y] != 'p' && board[x][y] != 'B'))
        {
            x += dx;
            y += dy;
        }
        if(x < 0 || x > 7 || y < 0 || y > 7)
            return false;
        if(board[x][y] == 'p')
            return true;
        return false;
    }
};
