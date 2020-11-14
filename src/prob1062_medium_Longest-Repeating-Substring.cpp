// prob1062: Longest Repeating Substring

/*
 * https://leetcode-cn.com/problems/longest-repeating-substring/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestRepeatingSubstring(string S) {
        vector<int> sa = get_sa(S);
        vector<int> lcp = get_lcp(S, sa);
        return *max_element(lcp.begin(), lcp.end());
    }

private:
    const int ALPHABET = 128;

    vector<int> get_lcp(const string& s, const vector<int>& sa)
    {
        int n = s.size();
        vector<int> rank(n);
        for(int i = 0; i < n; ++i)
            rank[sa[i]] = i;

        int h = 0;
        vector<int> lcp(n);
        lcp[0] = 0;
        for(int i = 0; i < n; ++i)
        {
            if(rank[i] == 0)
                continue;
            int j = sa[rank[i] - 1];

            // h 先减去首字母的 1 长度
            if(h > 0)
                --h;
            while(j + h < n && i + h < n && s[j + h] == s[i + h])
                ++h;

            lcp[rank[i] - 1] = h;
        }
        return lcp;
    }

    vector<int> get_sa(const string& s)
    {
        vector<int> c(ALPHABET);
        int n = s.size();
        vector<int> rank(n); // 第一关键字
        vector<int> y(n); // 第二关键字
        vector<int> sa(n);

        for(int i = 0; i < n; ++i)
        {
            ++c[s[i]];
            rank[i] = s[i];
        }
        for(int i = 1; i < ALPHABET; ++i)
            c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; --i)
        {
            sa[--c[rank[i]]] = i;
        }

        int m = ALPHABET; // 关键字种类数
        for(int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for(int i = n - k; i < n; ++i)
                y[p++] = i;
            for(int i = 0; i < n; ++i)
                if(sa[i] >= k)
                    y[p++] = sa[i] - k;

            c.assign(m, 0);
            for(int i = 0; i < n; ++i)
                ++c[rank[i]];
            for(int i = 1; i < m; ++i)
                c[i] += c[i - 1];
            for(int i = n - 1; i >= 0; --i)
                sa[--c[rank[y[i]]]] = y[i];

            rank.swap(y);
            p = 1; // 分配的关键字
            rank[sa[0]] = 0;
            for(int i = 1; i < n; ++i)
            {
                // 此时 y 持有的是长为 len 的第一关键字
                // 长为 len 的第二关键字从 sa 获得
                // 合并后的长为 len * 2 的第一关键字放在 rank
                if(y[sa[i - 1]] == y[sa[i]] &&
                        (sa[i - 1] + k >= n ? -1 : y[sa[i - 1] + k]) == (sa[i] + k >= n ? -1 : y[sa[i] + k]))
                    rank[sa[i]] = p - 1;
                else
                {
                    rank[sa[i]] = p;
                    p++;
                }
            }

            // 下一轮的关键字种类数
            if(p >= n)
                break;
            m = p;
        }

        return sa;
    }
};
