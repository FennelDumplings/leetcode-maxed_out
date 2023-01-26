// prob125: Valid Palindrome

/*
 * Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.
 * Note: For the purpose of this problem, we define empty string as valid palindrome.
 */

/*
 * Example 1:
 * Input: "A man, a plan, a canal: Panama"
 * Output: true
 * Example 2:
 * Input: "race a car"
 * Output: false
 */

#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        string tmp;
        for (auto c : s) {
            if (islower(c) || isdigit(c))  tmp += c;
            else if (isupper(c)) tmp += (c + 32);
        }
        int i = 0, j = tmp.size() - 1;
        while (i < j) {
            if (tmp[i] != tmp[j]) return false;
            i++;
            j--;
        }
        return true;
    }
};

// A: 65, a: 97, 0: 48
class Solution_2 {
public:
    bool isPalindrome(string s) {
        if(s.empty()) return true;
        int n = s.size();
        int l = 0, r = n - 1;
        while(l < r)
        {
            if(!_check_char(s, l))
            {
                ++l;
                continue;
            }
            if(!_check_char(s, r))
            {
                --r;
                continue;
            }
            if(!_check(s, l, r))
                return false;
            ++l, --r;
        }
        return true;
    }

private:
    bool _check_char(const string& s, int idx)
    {
        return (s[idx] - 'a' >= 0 && s[idx] - 'a' <= 25)
            || (s[idx] - 'A' >= 0 && s[idx] - 'A' <= 25)
            || (s[idx] - '0' >= 0 && s[idx] - '0' <= 9);
    }

    bool _check(const string& s, int l, int r)
    {
        if(s[l] == s[r]) return true;
        if((s[l] - 'A' >= 0 && s[l] - 'A' <= 25) && s[r] == s[l] + 32)
            return true;
        if((s[r] - 'A' >= 0 && s[r] - 'A' <= 25) && s[l] == s[r] + 32)
            return true;
        return false;
    }
};
