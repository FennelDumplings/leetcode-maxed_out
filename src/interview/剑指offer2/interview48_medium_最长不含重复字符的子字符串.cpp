// interview48: 最长不含重复字符的子字符串

/*
 * https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        int ans = 1;
        unordered_set<char> setting;
        int left = 0, right = 0;
        while(right < n)
        {
            while(right < n && setting.find(s[right]) == setting.end())
            {
                setting.insert(s[right]);
                ++right;
            }
            ans = max(ans, right - left);
            if(right == n) return ans;
            char dup = s[right];
            while(s[left] != dup)
            {
                setting.erase(setting.find(s[left]));
                ++left;
            }
            setting.erase(setting.find(s[left]));
            ++left;
        }
        return ans;
    }
};
