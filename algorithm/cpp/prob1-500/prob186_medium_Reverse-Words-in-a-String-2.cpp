// prob186. Reverse Words in a String II

/*
 * Given an input string , reverse the string word by word. 
 */

/*
 * Example:
 * Input:  ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
 * Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
 */

/*
 * Note: 
 * A word is defined as a sequence of non-space characters.
 * The input string does not contain leading or trailing spaces.
 * The words are always separated by a single space.
 * Follow up: Could you do it in-place without allocating extra space?
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void reverseWords(vector<char>& s) {
        if(s.empty()) return;
        reverse(s.begin(), s.end());
        int n = s.size();
        int left = 0;
        while(left < n)
        {
            int right = left;
            while(right < n && s[right] != ' ')
                ++right;
            reverse(s.begin() + left, s.begin() + right);
            left = right + 1;
        }
    }
};
