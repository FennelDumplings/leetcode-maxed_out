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
        int n1 = s1.size();
        int n2 = s2.size();
        if(n1 != n2) return false;
        if(n1 == 1 && n2 == 1) return s1[0] == s2[0];
        bool eq = true;
        if(!_equal(s1, s2, eq)) return false;
        _equal(s1, s2, eq);
        if(eq) return true;

        // 下面这种排序再判断两个串是否相等的办法比哈希表计数更快
        // string ss1 = s1, ss2 = s2;
        // sort(ss1.begin(), ss1.end()), sort(ss2.begin(), ss2.end());
        // if (ss1 != ss2) return false;

        for(int i = 1; i <= n1 - 1; ++i)
        {
            if(isScramble(s1.substr(0, i), s2.substr(0, i)) &&
                    isScramble(s1.substr(i, n1 - i), s2.substr(i, n2 - i)))
                return true;
            if(isScramble(s1.substr(0, i), s2.substr(n2 - i, i)) &&
                    isScramble(s1.substr(i, n1 - i), s2.substr(0, n2 - i)))
                return true;
        }
        return false;
    }

private:
    bool _equal(const string& str1, const string& str2, bool& eq)
    {
        int n = str1.size();
        unordered_map<char, int> hash1;
        unordered_map<char, int> hash2;
        eq = true;
        for(int i = 0; i < n; ++i)
        {
            if(str1[i] != str2[i]) eq = false;
            ++hash1[str1[i]];
            ++hash2[str2[i]];
        }
        if(eq) return true;
        if(hash1.size() != hash2.size()) return false;
        auto it1 = hash1.begin();
        while(it1 != hash1.end() )
        {
            if(hash2.find(it1 -> first) == hash2.end() || hash2[it1 -> first] != it1 -> second)
                return false;
            ++it1;
        }
        return true;
    }
};
