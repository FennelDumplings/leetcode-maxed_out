// interview58-1: 翻转单词顺序

/*
 * https://leetcode-cn.com/problems/fan-zhuan-dan-ci-shun-xu-lcof/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        if(s.empty()) return "";
        vector<string> items;
        int n = s.size();
        int left = 0;
        while(left < n)
        {
            while(left < n && s[left] == ' ')
                ++left;
            if(left == n) break;
            int right = left;
            while(right < n && s[right] != ' ')
                ++right;
            items.push_back(s.substr(left, right - left));
            left = right;
        }
        if(items.empty())
            return "";
        int m = items.size();
        string result;
        for(int i = m - 1; i >= 0; --i)
        {
            result += items[i] + ' ';
        }
        result.pop_back();
        return result;
    }
};
