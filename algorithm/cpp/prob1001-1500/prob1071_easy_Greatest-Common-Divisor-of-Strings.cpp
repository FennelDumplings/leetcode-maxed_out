// prob1071: Greatest Common Divisor of Strings

/*
 * https://leetcode-cn.com/problems/greatest-common-divisor-of-strings/
 */

#include <string>

using namespace std;

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        int l = gcd<int>(n, m);
        string X = str1.substr(0, l);
        int i = 0;
        while(i < n)
        {
            string cur = str1.substr(i, l);
            if(cur != X)
                return "";
            i += l;
        }
        i = 0;
        while(i < m)
        {
            string cur = str2.substr(i, l);
            if(cur != X)
                return "";
            i += l;
        }
        return X;
    }
};
