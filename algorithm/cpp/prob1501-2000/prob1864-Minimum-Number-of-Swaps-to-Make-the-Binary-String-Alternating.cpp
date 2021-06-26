
#include <cmath>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int minSwaps(string s) {
        int n = s.size();
        int n0 = 0, n1 = 0;
        for(const char& ch: s)
        {
            if(ch == '0')
                ++n0;
            else
                ++n1;
        }
        if(abs(n1 - n0) > 1)
            return -1;
        if(n & 1)
        {
            int diff = 0;
            if(n1 > n0)
            {
                // 10101 形式
                for(int i = 0; i < n; ++i)
                {
                    if(i & 1)
                        diff += s[i] != '0';
                    else
                        diff += s[i] != '1';
                }
            }
            else
            {
                // 01010 形式
                for(int i = 0; i < n; ++i)
                {
                    if(i & 1)
                        diff += s[i] != '1';
                    else
                        diff += s[i] != '0';
                }
            }
            return diff / 2;
        }
        else
        {
            int diff1 = 0; // 101010 形式
            int diff2 = 0; // 010101 形式
            for(int i = 0; i < n; ++i)
            {
                if(i & 1)
                {
                    diff1 += s[i] != '0';
                    diff2 += s[i] != '1';
                }
                else
                {
                    diff1 += s[i] != '1';
                    diff2 += s[i] != '0';
                }
            }
            return min(diff1, diff2) / 2;
        }
    }
};
