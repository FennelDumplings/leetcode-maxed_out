// prob1328: Break a Palindrome

/*
 * https://leetcode-cn.com/problems/break-a-palindrome/
 */

#include <string>

using namespace std;

class Solution {
public:
    string breakPalindrome(string palindrome) {
        int n = palindrome.size();
        for(int i = 0; i < n / 2; ++i)
        {
            if(palindrome[i] != 'a')
            {
                palindrome[i] = 'a';
                return palindrome;
            }
            if(i == n / 2 - 1)
            {
                palindrome[n - 1] = 'b';
                return palindrome;
            }
        }
        return "";
    }
};
