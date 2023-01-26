// prob1461: Check If a String Contains All Binary Codes of Size K

/*
 * https://leetcode-cn.com/problems/check-if-a-string-contains-all-binary-codes-of-size-k/
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
        int n = binaryString.size();

        //将二进制数字转换为十进制
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans *= 2;
            if (binaryString[i] == '1')
                ++ans;
        }

        return ans;
    }
};
