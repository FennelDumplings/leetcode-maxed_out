// prob161: One Edit Distance

/*
 * Given two strings s and t, determine if they are both one edit distance apart.
 * Note: 
 * There are 3 possiblities to satisify one edit distance apart:
 * Insert a character into s to get t
 * Delete a character from s to get t
 * Replace a character of s to get t
 */

/*
 *
 * Example 1:
 * Input: s = "ab", t = "acb"
 * Output: true
 * Explanation: We can insert 'c' into s to get t.
 * Example 2:
 * Input: s = "cab", t = "ad"
 * Output: false
 * Explanation: We cannot get t from s by only one step.
 * Example 3:
 * Input: s = "1203", t = "1213"
 * Output: true
 * Explanation: We can replace '0' with '1' to get t.
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int ns = s.size(), nt = t.size();
        int iter = 0;
        if(ns == nt)
        {
            while(iter < ns && s[iter] == t[iter])
                ++iter;
            if(iter == ns) return false;
            ++iter;
            while(iter < ns && s[iter] == t[iter])
                ++iter;
            if(iter != ns)
                return false;
            return true;
        }
        if(ns + 1 == nt)
        {
            while(iter < ns && s[iter] == t[iter])
                ++iter;
            if(iter == ns) return true;
            while(iter < ns && s[iter] == t[iter + 1])
                ++iter;
            if(iter != ns) return false;
            return true;
        }
        if(ns - 1 == nt)
            return isOneEditDistance(t, s);
        return false;
    }
};


