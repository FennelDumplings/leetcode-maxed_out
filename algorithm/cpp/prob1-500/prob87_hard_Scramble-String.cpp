// prob87: Scramble String

/*
 * Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
 * Below is one possible representation of s1 = "great":
 *     great
 *    /    \
 *   gr    eat
 *  / \    /  \
 * g   r  e   at
 *            / \
 *           a   t
 * To scramble the string, we may choose any non-leaf node and swap its two children.
 * For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat".
 *     rgeat
 *    /    \
 *   rg    eat
 *  / \    /  \
 * r   g  e   at
 *            / \
 *           a   t
 * We say that "rgeat" is a scrambled string of "great".
 * Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae".
 *     rgtae
 *    /    \
 *   rg    tae
 *  / \    /  \
 * r   g  ta  e
 *        / \
 *       t   a
 * We say that "rgtae" is a scrambled string of "great".
 * Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
 */

/*
 * Example 1:
 * Input: s1 = "great", s2 = "rgeat"
 * Output: true
 * Example 2:
 * Input: s1 = "abcde", s2 = "caebd"
 * Output: false
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        dp = unordered_set<int>();
        return solve(s1, 0, s1.size() - 1, s2, 0, s2.size() - 1);
    }

    unordered_set<int> dp;

    bool solve(const string& s1, int l1, int r1, const string& s2, int l2, int r2)
    {
        if(r1 - l1 != r2 - l2)
            return false;
        int n = r1 - l1 + 1;
        if(n == 1)
        {
            if(s1[l1] == s2[l2])
                return true;
            else
                return false;
        }
        int s = (l1 * 100 + r1) * 10000 + (l2 * 100 + r2);
        if(dp.count(s) > 0)
            return false;
        for(int i = 1; i < n; ++i)
        {
            if(solve(s1, l1, l1 + i - 1, s2, l2, l2 + i - 1)
                    && solve(s1, l1 + i, r1, s2, l2 + i, r2))
                return true;
            if(solve(s1, l1, l1 + i - 1, s2, r2 - i + 1, r2)
                    && solve(s1, l1 + i, r1, s2, l2, r2 - i))
                return true;
        }
        dp.insert(s);
        return false;
    }
};
