// prob866: Prime Palindrome

/*
 * https://leetcode-cn.com/problems/prime-palindrome/
 */

#include <cmath>
#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
    int primePalindrome(int N) {
        string N_str = to_string(N);
        int len = (N_str.size() + 1) / 2; // 回文根初始长度
        for(int l = len; l <= 5; ++l)
        {
            int start = pow(10, l - 1);
            // 查 2l-1 长的
            for(int r = start; r < pow(10, l); ++r)
            {
                string r_str = to_string(r);
                string p_str = r_str;
                auto it = ++r_str.rbegin();
                while(it != r_str.rend())
                {
                    p_str += *it;
                    ++it;
                }
                stringstream ss2;
                int nxt;
                ss2 << p_str;
                ss2 >> nxt;
                if(nxt >= N && isPrime(nxt))
                    return nxt;
            }
            // 查 2l 长的
            for(int r = start; r < pow(10, l); ++r)
            {
                string r_str = to_string(r);
                string p_str = r_str;
                auto it = r_str.rbegin();
                while(it != r_str.rend())
                {
                    p_str += *it;
                    ++it;
                }
                stringstream ss2;
                int nxt;
                ss2 << p_str;
                ss2 >> nxt;
                if(nxt >= N && isPrime(nxt))
                    return nxt;
            }
        }
        return -1;
    }

private:
    bool isPrime(int n)
    {
        if(n == 1)
            return false;
        for(int i = 2; i * i <= n; ++i)
            if(n % i == 0)
                return false;
        return true;
    }
};
