// interview50: 第一个只出现一次的字符

/*
 * https://leetcode-cn.com/problems/di-yi-ge-zhi-chu-xian-yi-ci-de-zi-fu-lcof/
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    char firstUniqChar(string s) {
        if(s.empty()) return ' ';
        unordered_map<char, int> mapping;
        for(const char& ch: s)
            ++mapping[ch];
        for(const char& ch: s)
            if(mapping[ch] == 1)
                return ch;
        return ' ';
    }
};
