// prob1415: The k-th Lexicographical String of All Happy Strings of Length n

/*
 * https://leetcode-cn.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/
 */

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    string getHappyString(int n, int k) {
        string result;
        if(3 * pow(2, n - 1) < k)
            return "";
        int len = n;
        while(len > 0)
        {
            // c := 限定上一个字符后，长为 len - 1 的开心串个数
            int c = pow(2, len - 1);
            int num = 1;
            for(char ch = 'a'; ch <= 'c'; ++ch)
            {
                if(!result.empty() && ch == result.back())
                    continue;
                if(num * c >= k)
                {
                    result += ch;
                    break;
                }
                ++num;
            }
            k -= (num - 1) * c;
            --len;
        }
        return result;
    }
};
