// prob293:

/*
 * You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -,
 * you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a
 * move and therefore the other person will be the winner.
 * Write a function to compute all possible states of the string after one valid move.
 * Note: If there is no valid move, return an empty list [].
 */

/*
 * Example:
 * Input: s = "++++"
 * Output:
 * [
 *   "--++",
 *   "+--+",
 *   "++--"
 * ]
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generatePossibleNextMoves(string s) {
        int n = s.size();
        if(n < 2) return vector<string>();
        vector<string> result;
        int i = 0;
        while(i < n)
        {
            while(i < n && s[i] == '-')
                ++i;
            if(i == n) break;
            int j = i;
            while(j < n && s[j] == '+')
                ++j;
            int len = j - i;
            if(len >= 2)
            {
                for(int k = i; k <= i + len - 2; ++k)
                {
                    string item = s;
                    item[k] = '-';
                    item[k + 1] = '-';
                    result.push_back(item);
                }
            }
            i = j;
        }
        return result;
    }
};
