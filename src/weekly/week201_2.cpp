
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    char findKthBit(int n, int k) {
        string s(1, '0');
        for(int i = 1; i < n; ++i)
        {
            string t(s.begin(), s.end());
            for(char &ch: t)
            {
                if(ch == '0')
                    ch = '1';
                else
                    ch = '0';
            }
            reverse(t.begin(), t.end());
            s = s + '1' + t;
        }
        return s[k - 1];
    }
};
