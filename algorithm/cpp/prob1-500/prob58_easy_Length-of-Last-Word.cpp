// prob58: Length of Last Word

/*
 * Given a string s consists of upper/lower-case alphabets and empty space characters ' ',
 * return the length of last word (last word means the last appearing word if we loop from left to right) in the string.
 * If the last word does not exist, return 0.
 * Note: A word is defined as a maximal substring consisting of non-space characters only.
 */

/*
 * Example:
 * Input: "Hello World"
 * Output: 5
 */

#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        int left = 0, right = 0;
        int result = 0;
        while(true)
        {
            while(left < n && s[left] == ' ')
                ++left;
            if(left == n) break;
            right = left;
            while(right < n && s[right] != ' ')
                ++right;
            result = right - left;
            if(right == n) break;
            left = right;
        }
        return result;
    }
};
