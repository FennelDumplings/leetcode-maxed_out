// interview01.09: 字符串轮转

/*
 * 字符串轮转。给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成（比如，waterbottle是erbottlewat旋转后的字符串）。
 */

#include <string>

using namespace std;

class Solution {
public:
    bool isFlipedString(string s1, string s2) {
        int n1 = s1.size(), n2 = s2.size();
        if(n1 != n2) return false;
        string s = s1 + s1;
        auto pos = s.find(s2);
        return pos != string::npos;
    }
};
