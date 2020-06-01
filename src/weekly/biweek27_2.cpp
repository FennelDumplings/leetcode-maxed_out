// 20200530
// 2. 检查一个字符串是否包含所有长度为 K 的二进制子串

/*
 * 给你一个二进制字符串 s 和一个整数 k 。
 * 如果所有长度为 k 的二进制字符串都是 s 的子串，请返回 True ，否则请返回 False 。
 */

/*
 * 示例 1：
 *
 * 输入：s = "00110110", k = 2
 * 输出：true
 * 解释：长度为 2 的二进制串包括 "00"，"01"，"10" 和 "11"。它们分别是 s 中下标为 0，1，3，2 开始的长度为 2 的子串。
 * 示例 2：
 *
 * 输入：s = "00110", k = 2
 * 输出：true
 * 示例 3：
 *
 * 输入：s = "0110", k = 1
 * 输出：true
 * 解释：长度为 1 的二进制串包括 "0" 和 "1"，显然它们都是 s 的子串。
 * 示例 4：
 *
 * 输入：s = "0110", k = 2
 * 输出：false
 * 解释：长度为 2 的二进制串 "00" 没有出现在 s 中。
 * 示例 5：
 *
 * 输入：s = "0000000001011100", k = 4
 * 输出：false
 */

/*
 * 提示：
 *
 * 1 <= s.length <= 5 * 10^5
 * s 中只含 0 和 1 。
 * 1 <= k <= 20
 */

#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
public:
    bool hasAllCodes(string s, int k) {
        vector<bool> mapping(pow(2, k), false);
        int n = s.size();
        for(int i = 0; i <= n - k; ++i)
            mapping[_binstr2dec(s.substr(i, k))] = true;
        for(bool flag: mapping)
            if(!flag)
                return false;
        return true;
    }

private:
    int _binstr2dec(const string& binaryString)
    {
        //在此处调用判断一个字符串有多长的函数
        int size = binaryString.size();

        //将二进制数字转换为十进制
        int parseBinary = 0;
        for (int i = size; i >= 0; --i)
        {
            if (binaryString[i] == '1')
                parseBinary += pow(2.0, i);
        }

        return parseBinary;
    }
};
