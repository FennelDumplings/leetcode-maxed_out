// prob1044: Longest Duplicate Substring

/*
 * https://leetcode-cn.com/problems/longest-duplicate-substring/
 */

#include <vector>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

class Solution_2 {
public:
    string longestDupSubstring(string S) {
        int n = S.size();
        int left = 0, right = n - 1;
        while(left < right)
        {
            int mid = (left + right + 1) / 2;
            int idx = check(S, mid);
            if(idx != -1)
                left = mid;
            else
                right = mid - 1;
        }
        if(left == 0) return "";
        int idx = check(S, left);
        return S.substr(idx, left);
    }

private:
    using ull = unsigned long long;
    const ull p = 201326611;
    unordered_map<ull, vector<int>> mapping; // hash -> idx

    int check(const string& S, int l)
    {
        int n = S.size();
        ull power = quick_pow(p, l - 1);
        ull hash = 0;
        for(int i = 0; i < l; ++i)
        {
            hash = hash * p;
            hash = hash + (ull)(S[i] - 'a');
        }
        mapping.clear();
        mapping[hash].push_back(0);
        for(int i = l; i < n; ++i)
        {
            hash = hash - (ull)(S[i - l] - 'a') * power;
            hash = hash * p;
            hash = hash + (ull)(S[i] - 'a');
            if(mapping.count(hash) > 0)
            {
                for(int j: mapping[hash])
                    if(check(S, l, j, i - l + 1))
                        return i - l + 1;
            }
            mapping[hash].push_back(i - l + 1);
        }
        return -1;
    }

    bool check(const string& S, int l, int i, int j)
    {
        for(int k = 0; k < l; ++k)
            if(S[i + k] != S[j + k])
                return false;
        return true;
    }

    ull quick_pow(ull a, ull n)
    {
        ull ans = 1;
        while(n)
        {
            if(n & 1)
                ans = ans * a;
            a = a * a;
            n >>= 1;
        }
        return ans;
    }
};

// -----------------------------

class Solution {
public:
    string longestDupSubstring(string S) {
        vector<int> sa = get_sa(S);
        vector<int> lcp = get_lcp(S, sa);
        int start = -1;
        int max_len = 0;
        int n = S.size();
        for(int i = 0; i < n; ++i)
        {
            if(lcp[i] > max_len)
            {
                max_len = lcp[i];
                start = sa[i];
            }
        }
        if(start == -1)
            return "";
        return S.substr(start, max_len);
    }

private:
    const int ALPHABET = 128;

    vector<int> get_sa(string_view s)
    {
        int n = s.size();
        vector<int> x(n), y(n);
        vector<int> sa(n);
        vector<int> c(ALPHABET);

        for(int i = 0; i < n; ++i)
        {
            ++c[s[i]];
            x[i] = s[i];
        }
        for(int i = 1; i < ALPHABET; ++i)
            c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; --i)
            sa[--c[x[i]]] = i;

        int m = ALPHABET;
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
                ++c[x[i]];
            for(int i = 1; i < m; ++i)
                c[i] += c[i - 1];
            for(int i = n - 1; i >= 0; --i)
                sa[--c[x[y[i]]]] = y[i];

            x.swap(y);
            x[sa[0]] = 0;
            p = 1;
            for(int i = 1; i < n; ++i)
            {
                if(y[sa[i - 1]] == y[sa[i]] &&
                        (sa[i - 1] + k >= n ? -1 : y[sa[i - 1] + k]) == (sa[i] + k >= n ? -1 : y[sa[i] + k]))
                    x[sa[i]] = p - 1;
                else
                    x[sa[i]] = p++;
            }

            if(p >= n)
                break;
            m = p;
        }
        return sa;
    }

private:
    vector<int> get_lcp(string_view s, const vector<int>& sa)
    {
        int n = s.size();
        vector<int> rank(n);
        for(int i = 0; i < n; ++i)
            rank[sa[i]] = i;

        vector<int> lcp(n);
        int h = 0;
        lcp[n - 1] = 0;
        for(int i = 0; i < n; ++i)
        {
            if(rank[i] == 0)
                continue;

            if(h > 0)
                --h;
            int j = sa[rank[i] - 1];
            while(i + h < n && j + h < n && s[i + h] == s[j + h])
                ++h;

            lcp[rank[i] - 1] = h;
        }
        return lcp;
    }
};
