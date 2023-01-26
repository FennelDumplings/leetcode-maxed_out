// prob680: Valid Palindrome II

/*
 * Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.
 */

/*
 * Example 1:
 * Input: "aba"
 * Output: True
 * Example 2:
 * Input: "abca"
 * Output: True
 * Explanation: You could delete the character 'c'.
 */

/*
 * Note:
 * The string will only contain lowercase characters a-z. The maximum length of the string is 50000.
 */

#include <string>

using namespace std;

class Solution {
public:
    bool validPalindrome(string s) {
        int n = s.size();
        if(n <= 2) return true;
        int left = 0, right = n - 1;
        bool del = false;
        while(left < right)
        {
            if(s[left] == s[right])
            {
                ++left;
                --right;
                continue;
            }
            if(del) return false;
            if(left + 1 == right) return true;
            if(left + 2 == right)
                return s[left] == s[left + 1] || s[right] == s[left + 1];
            // left + 1 < right - 1
            del = true;
            if(s[left + 1] != s[right] && s[left] != s[right - 1])
                return false;
            if(s[left + 1] != s[right])
                return _validPalindrome(s, left, right - 1);
            if(s[left] != s[right - 1])
                return _validPalindrome(s, left + 1, right);
            return _validPalindrome(s, left, right - 1) || _validPalindrome(s, left + 1, right);
        }
        return true;
    }

private:
    bool _validPalindrome(const string& s, int left, int right)
    {
        while(left < right)
        {
            if(s[left] != s[right])
                return false;
            ++left;
            --right;
        }
        return true;
    }
};

