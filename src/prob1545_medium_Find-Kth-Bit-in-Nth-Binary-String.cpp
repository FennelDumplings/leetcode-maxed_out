// prob1545: Find Kth Bit in Nth Binary String

/*
 * https://leetcode-cn.com/problems/find-kth-bit-in-nth-binary-string/
 */

#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// 模拟
class Solution_2 {
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

// 分治
class Solution {
public:
    char findKthBit(int n, int k) {
        if(n == 1)
            return '0';
        ll mid = pow(2, n - 1) - 1;
        if((ll)(k - 1) == mid) return '1';
        else if((ll)(k - 1) < mid)
            return findKthBit(n - 1, k);
        else
            return flip(findKthBit(n - 1, (pow(2, n) - 2 - (k - 1)) + 1));
    }

private:
    using ll = long long;

    char flip(const char& ch)
    {
        if(ch == '1')
            return '0';
        else
            return '1';
    }
};
