// prob1309: Decrypt String from Alphabet to Integer Mapping

/*
 * Given a string s formed by digits ('0' - '9') and '#' . We want to map s to English lowercase characters as follows:
 *
 * Characters ('a' to 'i') are represented by ('1' to '9') respectively.
 * Characters ('j' to 'z') are represented by ('10#' to '26#') respectively. 
 * Return the string formed after mapping.
 *
 * It's guaranteed that a unique mapping will always exist.
 */

/*
 * Example 1:
 *
 * Input: s = "10#11#12"
 * Output: "jkab"
 * Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".
 * Example 2:
 *
 * Input: s = "1326#"
 * Output: "acz"
 * Example 3:
 *
 * Input: s = "25#"
 * Output: "y"
 * Example 4:
 *
 * Input: s = "12345678910#11#12#13#14#15#16#17#18#19#20#21#22#23#24#25#26#"
 * Output: "abcdefghijklmnopqrstuvwxyz"
 */

/*
 * Constraints:
 *
 * 1 <= s.length <= 1000
 * s[i] only contains digits letters ('0'-'9') and '#' letter.
 * s will be valid string such that mapping is always possible.
 */

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    string freqAlphabets(string s) {
        string result;
        int left = 0;
        int n = s.size();
        while(left < n)
        {
            if(left + 2 < n && s[left + 2] == '#')
            {
                stringstream ss;
                ss << s.substr(left, 2);
                int num;
                ss >> num;
                result += 'a' + (num - 1);
                left += 3;
            }
            else
            {
                result += 'a' + s[left] - '1';
                ++left;
            }
        }
        return result;
    }
};
