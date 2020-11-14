// prob1163: Last Substring in Lexicographical Order

/*
 * https://leetcode-cn.com/problems/last-substring-in-lexicographical-order/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution_2 {
public:
    string lastSubstring(string s) {
        int n = s.size();
        vector<int> sa = get_sa(s);
        return s.substr(sa[n - 1]);
    }

private:
    vector<int> get_sa(const string& s)
    {
        int n = s.size();
        vector<int> sa(n);
        vector<int> rank(n);
        vector<pair<string, int>> suffixes;
        for(int i = 0; i < n; ++i)
            suffixes.emplace_back(s.substr(i), i);
        sort(suffixes.begin(), suffixes.end());
        for(int i = 0; i < n; ++i)
        {
            sa[i] = suffixes[i].second;
            rank[suffixes[i].second] = i;
        }
        return sa;
    }
};


// -----------------------

class Solution_3 {
public:
    string lastSubstring(string s) {
        int n = s.size();
        vector<int> sa = get_sa(s);
        return s.substr(sa[n]);
    }

private:
    struct Info
    {
        int key1, key2, i;
        Info(){}
        Info(int k1, int k2, int i):key1(k1),key2(k2),i(i){}
    };

    struct Cmp
    {
        bool operator()(const Info& info1, const Info& info2) const
        {
            if(info1.key1 == info2.key1)
                return info1.key2 < info2.key2;
            return info1.key1 < info2.key1;
        }
    };

    bool equal(const Info& info1, const Info& info2) const
    {
        return info1.key1 == info2.key1 && info1.key2 == info2.key2;
    }

    vector<int> get_sa(const string& s)
    {
        vector<int> c(128);
        for(char ch: s) ++c[ch];
        for(int i = 1; i < 128; ++i)
            c[i] += c[i - 1];

        int n = s.size();
        vector<int> rank(n);

        for(int i = 0; i < n; ++i)
            rank[i] = c[s[i]];

        for(int k = 1; k < n; k <<= 1)
        {
            vector<Info> info(n);
            for(int i = 0; i < n; ++i)
            {
                info[i].i = i;
                info[i].key1 = rank[i];
                if(i + k >= n)
                    info[i].key2 = 0;
                else
                    info[i].key2 = rank[i + k];
            }
            sort(info.begin(), info.end(), Cmp());
            int i = 0;
            bool flag = true;
            while(i < n)
            {
                int j = i;
                while(j < n && equal(info[i], info[j]))
                {
                    flag = false;
                    rank[info[j].i] = i + 1;
                    ++j;
                }
                i = j;
            }
            if(flag)
                break;
        }

        vector<int> sa(n + 1);
        for(int i = 0; i < n; ++i)
        {
            sa[rank[i]] = i;
        }

        return sa;
    }
};

// ---------------------------------------------

class Solution {
public:
    string lastSubstring(string s) {
        int n = s.size();
        vector<int> sa = get_sa(s);
        return s.substr(sa[n - 1]);
    }

private:
    const int ALPHABET = 128;

    vector<int> get_sa(const string& s)
    {
        vector<int> c(ALPHABET);
        int n = s.size();
        vector<int> rank(n); // 第一关键字
        vector<int> y(n); // 第二关键字
        vector<int> sa(n + 1);

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
            p = 1;
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
