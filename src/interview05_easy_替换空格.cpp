// interview05: 替换空格

/*
 * 请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
 */

/*
 * 示例 1：
 * 输入：s = "We are happy."
 * 输出："We%20are%20happy."
 */

#include <string>

using namespace std;

class Solution {
public:
    string replaceSpace(string s) {
        string result = "";
        for(const char &ch: s)
        {
            if(ch == ' ')
                result += "%20";
            else
                result += ch;
        }
        return result;
    }
};
