// prob751: IP to CIDR

/*
 * https://leetcode-cn.com/problems/ip-to-cidr/
 */

#include <vector>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

using ull = unsigned long long;

class Solution {
public:
    vector<string> ipToCIDR(string ip, int n) {
        // 1 <= n < = 1000
        ull start = ip2uint(ip);
        ull end = start + n - 1;
        vector<string> result;
        solve(start, end, result);
        return result;
    }

private:
    void solve(ull left, ull right, vector<string>& result)
    {
        if(left > right) return;
        if(left == right)
        {
            string part = uint2ip(left);
            part += '/' + to_string(32);
            result.push_back(part);
            return;
        }
        // left < right
        int len = common_prefix_len(left, right);
        // len ... 31 逐个尝试(32的话，前面 left == right 那步特判就返回了)
        ull L = 0, R = 0;
        get_LR(left, len, L, R);
        // L<=left   right>=R
        if(left == L && R == right)
        {
            string part = uint2ip(L);
            part += '/' + to_string(len);
            result.push_back(part);
            return;
        }
        // L > left 或 right < R
        get_LR(left, len + 1, L, R);
        L |= (1 << (32 - (len + 1)));
        R &= ~(1 << (32 - (len + 1)));
        solve(left, R, result);
        solve(L, right, result);
    }

    void get_LR(ull x, int l, ull& L, ull& R)
    {
        L = x, R = x;
        L &= ~((1 << (32 - l)) - 1);
        R |= ((1 << (32 - l)) - 1);
    }

    string uint2ip(ull x)
    {
        string ans;
        ull mask = pow(2, 8) - 1;
        for(int i = 3; i >= 0; --i)
        {
            // 8 * i
            ull part = (x >> (8 * i)) & mask;
            ans += to_string(part) + '.';
        }
        ans.pop_back();
        return ans;
    }

    ull ip2uint(const string& ip)
    {
        int n = ip.size();
        ull ans = 0;
        int i = 0;
        while(i < n)
        {
            int j = i;
            while(j < n && ip[j] != '.')
                ++j;
            ull k;
            stringstream ss;
            ss << ip.substr(i, j - i);
            ss >> k;
            ans <<= 8;
            ans += k;
            i = j + 1;
        }
        return ans;
    }

    int common_prefix_len(ull x, ull y)
    {
        // x < y
        int i = 31;
        while(i >= 0 && ((x >> i) & 1) == ((y >> i) & 1))
            --i;
        int len = 32 - i - 1;
        return len;
    }
};
