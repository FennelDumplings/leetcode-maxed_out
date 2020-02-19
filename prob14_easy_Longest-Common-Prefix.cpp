// prob: Longest Common Prefix

/*
 * Write a function to find the longest common prefix string amongst an array of strings.
 *
 * If there is no common prefix, return an empty string "".
 */

/*
 * Example 1:
 * Input: ["flower","flow","flight"]
 * Output: "fl"
 * Example 2:
 * Input: ["dog","racecar","car"]
 * Output: ""
 * Explanation: There is no common prefix among the input strings.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        // string result = "";
        if(strs.empty()) return "";
        int n = strs.size();
        int iter = 0; // 遍历字符串的索引
        while(true)
        {
            char cur_iter = ' ';
            if(!current_char(strs[0], iter, cur_iter))
                return strs[0].substr(0, iter);
            char cur = ' ';
            for(int i = 1; i < n; ++i)
            {
                if(!current_char(strs[i], iter, cur) || cur != cur_iter)
                    return strs[0].substr(0, iter);
            }
            ++iter;
        }
    }

private:
    bool current_char(const string &str, int index, char &cur)
    {
        int n = str.size();
        if(index < n)
        {
            cur = str[index];
            return true;
        }
        else
            return false;
    }
};
