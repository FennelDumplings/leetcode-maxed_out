// interview01.02: Check Permutation LCCI

/*
 * Given two strings,write a method to decide if one is a permutation of the other.
 */

/*
 * Example 1:
 * Input: s1 = "abc", s2 = "bca"
 * Output: true
 * Example 2:
 * Input: s1 = "abc", s2 = "bad"
 * Output: false
 */

/*
 * Note:
 * 0 <= len(s1) <= 100
 * 0 <= len(s2) <= 100
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool CheckPermutation(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        if(n1 != n2) return false;
        unordered_map<char, int> char_cnt;
        for(char c: s1)
            ++char_cnt[c];
        for(char c: s2)
        {
            if(char_cnt.find(c) == char_cnt.end() || char_cnt[c] == 0)
                return false;
            --char_cnt[c];
        }
        return true;
    }
};
