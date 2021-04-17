// prob205: Isomorphic Strings

/*
 * Given two strings s and t, determine if they are isomorphic.
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 * All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.
 */

/*
 * Example 1:
 * Input: s = "egg", t = "add"
 * Output: true
 * Example 2:
 * Input: s = "foo", t = "bar"
 * Output: false
 * Example 3:
 * Input: s = "paper", t = "title"
 * Output: true
 */

/*
 * Note:
 * You may assume both s and t have the same length.
 */

#include <string>
#include <unordered_map>

using namespace std;

// 两个哈希表
// 一个判断单射，一个判断满射
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int n = s.size();
        unordered_map<char, char> mapping;
        unordered_map<char, char> mapping_reverse;
        for(int i = 0; i < n; ++i)
        {
            char cs = s[i], ct = t[i];
            auto it = mapping.find(ct);
            if(it == mapping.end())
            {
                mapping[ct] = cs;
            }
            else
            {
                if(mapping[ct] != cs)
                    return false;
            }
            auto it_reverse = mapping_reverse.find(cs);
            if(it_reverse == mapping_reverse.end())
            {
                mapping_reverse[cs] = ct;
            }
            else
            {
                if(mapping_reverse[cs] != ct)
                    return false;
            }
        }
        return true;
    }
};
