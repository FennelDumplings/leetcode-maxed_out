// prob541: Reverse String II

/*
 * Given a string and an integer k, you need to reverse the first k characters for every 2k characters
 * counting from the start of the string. If there are less than k characters left, reverse all of them. If
 * there are less than 2k but greater than or equal to k characters, then reverse the first k characters and
 * left the other as original.
 */

/*
 * Example:
 * Input: s = "abcdefg", k = 2
 * Output: "bacdfeg"
 */

/*
 * Restrictions:
 * The string consists of lower English letters only.
 * Length of the given string and k will in the range [1, 10000]
 */

#include <string>

using namespace std;

class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        int left = 0;
        while(left < n)
        {
            int right = min(left + k * 2 - 1, n - 1);
            if(right - left + 1 >= k)
                _reverseStr(s, left, left + k - 1);
            else
                _reverseStr(s, left, right);
            left = right + 1;
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
