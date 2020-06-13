// prob1392: Longest Happy Prefix

/*
 * A string is called a happy prefix if is a non-empty prefix which is also a suffix (excluding itself).
 * Given a string s. Return the longest happy prefix of s .
 * Return an empty string if no such prefix exists.
 */

/*
 * Example 1:
 * Input: s = "level"
 * Output: "l"
 * Explanation: s contains 4 prefix excluding itself ("l", "le", "lev", "leve"), and suffix ("l", "el", "vel", "evel"). The largest prefix which is also suffix is given by "l".
 * Example 2:
 * Input: s = "ababab"
 * Output: "abab"
 * Explanation: "abab" is the largest prefix which is also suffix. They can overlap in the original string.
 * Example 3:
 * Input: s = "leetcodeleet"
 * Output: "leet"
 * Example 4:
 * Input: s = "a"
 * Output: ""
 */

#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    void getNext(const string& s, vector<int>& nxt) {
        int n = s.size();
        for(int i = 1, j = 0; i < n; ++i)
        {
            while(j > 0 && s[i] != s[j])
                j = nxt[j];
            if(s[i] == s[j])
                ++j;
            nxt[i + 1] = j;
        }
    }

    string longestPrefix(string s) {
        int n = s.size();
        vector<int> nxt(n + 1, 0);
        getNext(s, nxt);
        int len = nxt.back();
        return s.substr(0, len);
    }
};
