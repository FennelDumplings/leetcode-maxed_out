// interview01.01: Is Unique LCCI

/*
 * Implement an algorithm to determine if a string has all unique characters. What if you cannot use additional data structures?
 */

/*
 * Example 1:
 * Input: s = "leetcode"
 * Output: false
 * Example 2:
 * Input: s = "abc"
 * Output: true
 */

/*
 * Note:
 * 0 <= len(s) <= 100
 */

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isUnique(string astr) {
        int n = astr.size();
        if(n <= 1) return true;
        unordered_set<char> setting;
        for(char c: astr)
        {
            if(setting.find(c) != setting.end())
                return false;
            setting.insert(c);
        }
        return true;
    }
};

// 位运算
class Solution_2 {
public:
    bool isUnique(string astr) {
        int n = astr.size();
        if(n <= 1) return true;
        int setting = 0;
        for(char c: astr)
        {
            if(setting & (1 << (c - 'a')))
                return false;
            setting |= (1 << (c - 'a'));
        }
        return true;
    }
};

