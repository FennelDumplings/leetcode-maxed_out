// prob482: License Key Formatting

/*
 * https://leetcode-cn.com/problems/license-key-formatting/
 */

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string licenseKeyFormatting(string S, int K) {
        int n = S.size();
        string result;
        int iter = n - 1;
        while(iter >= 0)
        {
            string buf;
            while(iter >= 0 && (int)buf.size() < K)
            {
                if(S[iter] != '-')
                {
                    buf += S[iter];
                    if(buf.back() >= 'a' && buf.back() <= 'z')
                        buf.back() = buf.back() - ('a' - 'A');
                }
                --iter;
            }
            if(!buf.empty())
                result += buf + '-';
        }
        if(!result.empty())
            result.pop_back();
        reverse(result.begin(), result.end());
        return result;
    }
};
