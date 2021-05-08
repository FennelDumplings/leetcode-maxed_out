// prob738: Monotone Increasing Digits

/*
 * https://leetcode-cn.com/problems/monotone-increasing-digits/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int N) {
        vector<int> digits;
        while(N)
        {
            digits.push_back(N % 10);
            N /= 10;
        }
        int m = digits.size();
        // 1245 -> [5,4,2,1]
        int cur = 0;
        vector<int> result(m, -1);
        bool flag = false;
        for(int i = m - 1; i >= 0; --i)
        {
            if(flag)
            {
                result[m - i - 1] = 9;
                continue;
            }
            if(digits[i] >= cur)
            {
                result[m - i - 1] = digits[i];
                cur = digits[i];
            }
            else
            {
                flag = true;
                int iter = m - i - 2;
                while(iter >= 1 && result[iter] == result[iter - 1])
                    --iter;
                --result[iter];
                ++iter;
                while(iter <= m - i - 2)
                    result[iter++] = 9;
                result[m - i - 1] = 9;
            }
        }
        int ans = 0;
        for(int d: result)
        {
            ans *= 10;
            ans += d;
        }
        return ans;
    }
};
