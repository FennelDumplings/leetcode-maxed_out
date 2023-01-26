// prob1177: Can Make Palindrome from Substring

/*
 * https://leetcode-cn.com/problems/can-make-palindrome-from-substring/
 */

#include <vector>
#include <string>

using namespace std;

class Solution_2 {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<vector<int>> prefix_cnts(n + 1, vector<int>(26));
        for(int i = 1; i <= n; ++i)
        {
            prefix_cnts[i] = prefix_cnts[i - 1];
            ++prefix_cnts[i][s[i - 1] - 'a'];
        }
        int m = queries.size();
        vector<bool> result(m, false);
        for(int i = 0; i < m; ++i)
        {
            int l = queries[i][0], r = queries[i][1];
            int k = queries[i][2];
            vector<int> cnt(26);
            for(int j = 0; j < 26; ++j)
                cnt[j] = prefix_cnts[r + 1][j] - prefix_cnts[l][j];
            int x = 0;
            for(int c: cnt)
                if(c & 1)
                    ++x;
            x /= 2; // 需要的次数
            if(x <= k)
                result[i] = true;
        }
        return result;
    }
};


class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int n = s.size();
        vector<int> prefix_cnts(n + 1);
        for(int i = 1; i <= n; ++i)
        {
            prefix_cnts[i] = prefix_cnts[i - 1];
            prefix_cnts[i] ^= 1 << (s[i - 1] - 'a');
        }
        int m = queries.size();
        vector<bool> result(m, false);
        for(int i = 0; i < m; ++i)
        {
            int l = queries[i][0], r = queries[i][1];
            int k = queries[i][2];
            int cnt;
            for(int j = 0; j < 26; ++j)
                cnt = prefix_cnts[r + 1] ^ prefix_cnts[l];
            int x = 0;
            for(int j = 0; j < 26; ++j)
                if(cnt >> j & 1)
                    ++x;
            x /= 2; // 需要的次数
            if(x <= k)
                result[i] = true;
        }
        return result;
    }
};
