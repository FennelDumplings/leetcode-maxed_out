// prob409: Longest Palindrome

/*
 * Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
 * This is case sensitive, for example "Aa" is not considered a palindrome here.
 * Note:
 * Assume the length of given string will not exceed 1,010.
 */

/*
 * Example:
 * Input:
 * "abccccdd"
 * Output:
 * 7
 * Explanation:
 * One longest palindrome that can be built is "dccaccd", whose length is 7.
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestPalindrome(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        if(n == 1) return 1;

        unordered_map<char, int> mapping;
        for(char c: s)
            ++mapping[c];

        int result = 0;
        bool have_odd = false;
        for(auto it = mapping.begin(); it != mapping.end(); ++it)
        {
            int count = it -> second;
            if(count & 1)
            {
                result += count - 1;
                have_odd = true;
            }
            else
                result += count;
        }
        if(have_odd) ++result;
        return result;
    }
};
