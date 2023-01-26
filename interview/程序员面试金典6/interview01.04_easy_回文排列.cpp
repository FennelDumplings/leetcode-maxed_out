// interview01.04: 回文排列

/*
 * 给定一个字符串，编写一个函数判定其是否为某个回文串的排列之一。
 * 回文串是指正反两个方向都一样的单词或短语。排列是指字母的重新排列。
 * 回文串不一定是字典当中的单词。
 */

/*
 * 示例1：
 * 输入："tactcoa"
 * 输出：true（排列有"tacocat"、"atcocta"，等等）
 */

#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canPermutePalindrome(string s) {
        unordered_map<char, int> mapping;
        for(const char& ch: s)
            ++mapping[ch];
        bool odd_flag = false;
        for(auto item: mapping)
        {
            if(item.second & 1)
            {
                if(odd_flag)
                    return false;
                odd_flag = true;
            }
        }
        return true;
    }
};
