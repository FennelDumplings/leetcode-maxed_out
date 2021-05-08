// prob1275: Find Winner on a Tic Tac Toe Game

/*
 * Tic-tac-toe is played by two players A and B on a 3 x 3 grid.
 * Here are the rules of Tic-Tac-Toe:
 * Players take turns placing characters into empty squares (" ").
 * The first player A always places "X" characters, while the second player B always places "O" characters.
 * "X" and "O" characters are always placed into empty squares, never on filled ones.
 * The game ends when there are 3 of the same (non-empty) character filling any row, column, or diagonal.
 * The game also ends if all squares are non-empty.
 * No more moves can be played if the game is over.
 * Given an array moves where each element is another array of size 2 corresponding to the row and column of the grid
 * where they mark their respective character in the order in which A and B play.
 * Return the winner of the game if it exists (A or B), in case the game ends in a draw return "Draw", if
 * there are still movements to play return "Pending".
 * You can assume that moves is valid (It follows the rules of Tic-Tac-Toe), the grid is initially empty and A will play first.
 */

/*
 * Example 1:
 * Input: moves = [[0,0],[2,0],[1,1],[2,1],[2,2]]
 * Output: "A"
 * Explanation: "A" wins, he always plays first.
 * "X  "    "X  "    "X  "    "X  "    "X  "
 * "   " -> "   " -> " X " -> " X " -> " X "
 * "   "    "O  "    "O  "    "OO "    "OOX"
 * Example 2:
 * Input: moves = [[0,0],[1,1],[0,1],[0,2],[1,0],[2,0]]
 * Output: "B"
 * Explanation: "B" wins.
 * "X  "    "X  "    "XX "    "XXO"    "XXO"    "XXO"
 * "   " -> " O " -> " O " -> " O " -> "XO " -> "XO "
 * "   "    "   "    "   "    "   "    "   "    "O  "
 * Example 3:
 * Input: moves = [[0,0],[1,1],[2,0],[1,0],[1,2],[2,1],[0,1],[0,2],[2,2]]
 * Output: "Draw"
 * Explanation: The game ends in a draw since there are no moves to make.
 * "XXO"
 * "OOX"
 * "XOX"
 * Example 4:
 * Input: moves = [[0,0],[1,1]]
 * Output: "Pending"
 * Explanation: The game has not finished yet.
 * "X  "
 * " O "
 * "   "
 */

/*
 * Constraints:
 * 1 <= moves.length <= 9
 * moves[i].length == 2
 * 0 <= moves[i][j] <= 2
 * There are no repeated elements on moves.
 * moves follow the rules of tic tac toe.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string tictactoe(vector<vector<int>>& moves) {
        // Return the winner of the game if it exists (A or B), in case the game ends in a draw return "Draw",
        // if there are still movements to play return "Pending".
        if(moves.empty()) return "Pending";
        int n = moves.size();
        vector<vector<char> > state(3, vector<char>(3, ' '));
        for(int i = 0; i < n; ++i)
        {
            if(i & 1)
                state[moves[i][0]][moves[i][1]] = 'O';
            else
                state[moves[i][0]][moves[i][1]] = 'X';
        }
        if(_check(moves[n - 1][0], moves[n - 1][1], state))
        {
            if(n & 1) return "A";
            else return "B";
        }
        if(n == 9) return "Draw";
        return "Pending";
    }

private:
    bool _check(int row, int col, vector<vector<char> > state)
    {
        char cur = state[row][col];
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


