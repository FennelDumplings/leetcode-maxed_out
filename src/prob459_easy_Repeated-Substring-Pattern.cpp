// prob459: Repeated Substring Pattern

/*
 * Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
 */

/*
 * Example 1:
 *
 * Input: "abab"
 * Output: True
 * Explanation: It's the substring "ab" twice.
 * Example 2:
 *
 * Input: "aba"
 * Output: False
 * Example 3:
 *
 * Input: "abcabcabcabc"
 * Output: True
 * Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int n = s.size();
        vector<int> mpnext = get_mp_next(s);
        return mpnext[n] && n % (n - mpnext[n]) == 0;

    }

private:
    vector<int> get_mp_next(const string& p)
    {
        int m = p.size();
        vector<int> mpnext(m + 1, -1);
        for(int i = 0, j = -1; i < m; ++i)
        {
            while(j > -1 && p[i] != p[j])
                j = mpnext[j];
            // j == -1 或 p[i] == p[j]
            ++j;
            mpnext[i + 1] = j;
        }
        return mpnext;
    }
};
