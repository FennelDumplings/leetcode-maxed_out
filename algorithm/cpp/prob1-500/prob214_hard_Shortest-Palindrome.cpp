// prob214: Shortest Palindrome

/*
 * Given a string s, you are allowed to convert it to a palindrome by adding characters in front of it.
 * Find and return the shortest palindrome you can find by performing this transformation.
 */

/*
 * Example 1:
 * Input: "aacecaaa"
 * Output: "aaacecaaa"
 * Example 2:
 * Input: "abcd"
 * Output: "dcbabcd"
 */

#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        if(s.empty()) return "";
        int m = s.size();
        string t = s + '#' + s;
        reverse(t.begin() + m + 1, t.end());
        vector<int> nxt = get_mpnext(t);
        int n_add = s.size() - nxt.back();
        string result = s.substr(m - n_add);
        reverse(result.begin(), result.end());
        result += s;
        return result;
    }

private:
    vector<int> get_mpnext(const string& p)
    {
        int m = p.size();
        vector<int> nxt(m + 1, 0);
        for(int i = 1, j = 0; i < m; ++i)
        {
            while(j > 0 && p[j] != p[i])
                j = nxt[j];
            if(p[i] == p[j])
                ++j;
            nxt[i + 1] = j;
        }
        return nxt;
    }
};
