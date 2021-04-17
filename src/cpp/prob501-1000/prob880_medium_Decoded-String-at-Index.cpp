// prob880: Decoded String at Index

/*
 * https://leetcode-cn.com/problems/decoded-string-at-index/
 */

#include <string>
#include <vector>
#include <list>

using namespace std;

class Solution_2 {
public:
    string decodeAtIndex(string S, int K) {
        int n = S.size();
        string str;
        for(int i = 0; i < n; ++i)
        {
            const char &ch = S[i];
            if(ch >= 'a' && ch <= 'z')
            {
                str += ch;
                if(--K == 0)
                    return string(1, ch);
            }
            else
            {
                int k = ch - '0';
                int s = str.size();
                if(s * (k - 1) >= K)
                    return string(1, str[(K - 1) % s]);
                else
                {
                    K -= s * (k - 1);
                    for(int j = 0; j < k - 1; ++j)
                        for(int p = 0; p < s; ++p)
                            str += str[p];
                }
            }
        }
        return "-1";
    }
};


class Solution {
public:
    string decodeAtIndex(string S, int K) {
        using ll = long long;
        int n = S.size();
        int left = 0;
        vector<string> strs;
        vector<ll> nums;
        vector<ll> lens;
        // num1, num2, ..., numm
        // str1, str2, ..., strm
        // len1, len2, ..., lenm
        // len[i] = (prev_len + num[i]) * num[i]
        ll prev_len = 0;
        while(left < n)
        {
            int right = left;
            while(right < n && S[right] >= 'a' && S[right] <= 'z')
                ++right;
            strs.push_back(S.substr(left, right - left));
            left = right;
            while(right < n && S[right] >= '2' && S[right] <= '9')
                ++right;
            ll num = 1;
            while(left < right && num <= K)
            {
                int a = S[left] - '0';
                num *= a;
                ++left;
            }
            nums.push_back(num);
            ll len = num * (prev_len + strs.back().size());
            lens.push_back(len);
            if(len >= K)
                break;
        }
        int k = lens.size() - 1;
        while(k >= 0)
        {
            int l = lens[k] / nums[k];
            int offset = (K - 1 + l) % l + 1;
            if(k == 0)
                return string(1, strs[k][offset - 1]);
            if(lens[k - 1] < offset)
                return string(1, strs[k][offset - lens[k - 1] - 1]);
            K = offset;
            --k;
        }
        return "-1";
    }
};
