// interview58-2: 左旋转字符串

/*
 * https://leetcode-cn.com/problems/zuo-xuan-zhuan-zi-fu-chuan-lcof/
 */

#include <string>

using namespace std;

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        // s << n
        string result = "";
        result += s.substr(n);
        result += s.substr(0, n);
        return result;
    }
};
