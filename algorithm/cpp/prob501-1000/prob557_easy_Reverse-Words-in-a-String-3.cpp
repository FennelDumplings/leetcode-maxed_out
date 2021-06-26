// prob557: Reverse Words in a String III

/*
 * Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
 */

/*
 * Example 1:
 * Input: "Let's take LeetCode contest"
 * Output: "s'teL ekat edoCteeL tsetnoc"
 */

/*
 * Note: In the string, each word is separated by single space and there will not be any extra space in the string.
 */

#include <string>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        if(s.empty()) return "";
        int n = s.size();
        int left = 0;
        while(left < n)
        {
            while(left < n && s[left] == ' ')
                ++left;
            if(left == n) return s;
            int right = left;
            while(right < n && s[right] != ' ')
                ++right;
            _reverseStr(s, left, right - 1);
            left = right;
        }
        return s;
    }

private:
    void _reverseStr(string& s, int left, int right)
    {
        while(left < right)
        {
            swap(s[left], s[right]);
            ++left;
            --right;
        }
    }
};
