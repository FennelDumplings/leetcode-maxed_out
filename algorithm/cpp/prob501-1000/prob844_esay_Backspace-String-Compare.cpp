// prob844: Backspace String Compare

/*
 * Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.
 */

/*
 * Example 1:
 * Input: S = "ab#c", T = "ad#c"
 * Output: true
 * Explanation: Both S and T become "ac".
 * Example 2:
 * Input: S = "ab##", T = "c#d#"
 * Output: true
 * Explanation: Both S and T become "".
 * Example 3:
 * Input: S = "a##c", T = "#a#c"
 * Output: true
 * Explanation: Both S and T become "c".
 * Example 4:
 * Input: S = "a#c", T = "b"
 * Output: false
 * Explanation: S becomes "c" while T becomes "b".
 */

/*
 * Note:
 * 1 <= S.length <= 200
 * 1 <= T.length <= 200
 * S and T only contain lowercase letters and '#' characters.
 */

#include <string>

using namespace std;

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int n = S.size(), m = T.size();
        int r1 = n - 1, r2 = m - 1;
        while(true)
        {
            int count1 = 0, count2 = 0;
            // S串的下一个位置
            while(r1 >= 0 && (count1 > 0 || S[r1] == '#' ))
            {
                if(S[r1] == '#')
                    ++count1;
                else
                    --count1;
                --r1;
            }
            while(r2 >= 0 && (count2 > 0 || T[r2] == '#' ))
            {
                if(T[r2] == '#')
                    ++count2;
                else
                    --count2;
                --r2;
            }
            if(r1 < 0 && r2 < 0) return true;
            if(r1 < 0 || r2 < 0) return false;
            if(S[r1] != T[r2]) return false;
            --r1;
            --r2;
        }
    }
};
