// prob422: Valid Word Square

/*
 * Given a sequence of words, check whether it forms a valid word square.
 * A sequence of words forms a valid word square if the kth row and column read the exact same string, where 0 ≤ k < max(numRows, numColumns).
 * Note:
 * The number of words given is at least 1 and does not exceed 500.
 * Word length will be at least 1 and does not exceed 500.
 * Each word contains only lowercase English alphabet a-z.
 */

/*
 * Example 1:
 * Input:
 * [
 *   "abcd",
 *   "bnrt",
 *   "crmy",
 *   "dtye"
 * ]
 * Output:
 * true
 * Explanation:
 * The first row and first column both read "abcd".
 * The second row and second column both read "bnrt".
 * The third row and third column both read "crmy".
 * The fourth row and fourth column both read "dtye".
 * Therefore, it is a valid word square.
 * Example 2:
 * Input:
 * [
 *   "abcd",
 *   "bnrt",
 *   "crm",
 *   "dt"
 * ]
 * Output:
 * true
 * Explanation:
 * The first row and first column both read "abcd".
 * The second row and second column both read "bnrt".
 * The third row and third column both read "crm".
 * The fourth row and fourth column both read "dt".
 * Therefore, it is a valid word square.
 * Example 3:
 * Input:
 * [
 *   "ball",
 *   "area",
 *   "read",
 *   "lady"
 * ]
 * Output:
 * false
 * Explanation:
 * The third row reads "read" while the third column reads "lead".
 * Therefore, it is NOT a valid word square.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        int n = words.size(), m = words[0].size();
        for(const string& str: words)
            m = max(m, (int)str.size());
        if(m != n) return false;
        vector<string> board(words.begin(), words.end());
        for(string &str: board)
            str += string(m - (int)str.size(), ' ');
        for(int k = 0; k < n; ++k)
            if(!_check(board, k))
                return false;
        return true;
    }

private:
    bool _check(const vector<string>& board, int k)
    {
        string str = board[k];
        int n = board.size();
        for(int i = 0; i < n; ++i)
        {
            if(board[i][k] != board[k][i])
                return false;
        }
        return true;
    }
};
