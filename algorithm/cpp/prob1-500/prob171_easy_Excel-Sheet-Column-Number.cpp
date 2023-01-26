// prob171: Excel Sheet Column Number

/*
 * Given a column title as appear in an Excel sheet, return its corresponding column number.
 * For example:
 *     A -> 1
 *     B -> 2
 *     C -> 3
 *     ...
 *     Z -> 26
 *     AA -> 27
 *     AB -> 28
 *     ...
 */

/*
 * Example 1:
 * Input: "A"
 * Output: 1
 * Example 2:
 * Input: "AB"
 * Output: 28
 * Example 3:
 * Input: "ZY"
 * Output: 701
 */

#include <string>

using namespace std;

class Solution {
public:
    int titleToNumber(string s) {
        if(s.empty()) return 0;
        int result = (s[0] - 'A') + 1;
        int n = s.size();
        for(int i = 1; i < n; ++i)
        {
            result *= 26;
            result += (s[i] - 'A') + 1;
        }
        return result;
    }
};
