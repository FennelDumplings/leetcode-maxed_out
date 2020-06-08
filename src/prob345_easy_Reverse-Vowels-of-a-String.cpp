// prob345: Reverse Vowels of a String

/*
 * Write a function that takes a string as input and reverse only the vowels of a string.
 * Example 1:
 * Input: "hello"
 * Output: "holle"
 * Example 2:
 * Input: "leetcode"
 * Output: "leotcede"
 * Note:
 * The vowels does not include the letter "y".
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    string reverseVowels(string s) {
        if(s.empty()) return s;
        int n = s.size();
        unordered_set<char> setting{'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
        int left = 0, right = n - 1;
        while(left < right)
        {
            if(setting.find(s[left]) != setting.end() && setting.find(s[right]) != setting.end())
            {
                swap(s[left], s[right]);
                ++left;
                --right;
            }
            else if(setting.find(s[left]) != setting.end())
            {
                --right;
            }
            else if(setting.find(s[right]) != setting.end())
            {
                ++left;
            }
            else
            {
                ++left;
                --right;
            }
        }
        return s;
    }
};
