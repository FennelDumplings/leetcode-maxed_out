// interview17.17: 多次搜索

/*
 * https://leetcode-cn.com/problems/multi-search-lcci/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<int>> multiSearch(string big, vector<string>& smalls) {
        if(smalls.empty()) return {};
        int n = smalls.size();
        vector<vector<int>> result(n, vector<int>());
        for(int i = 0; i < n; ++i)
        {
            if(smalls[i].empty()) continue;
            const string &w = smalls[i];
            match(big, w, result[i]);
        }
        return result;
    }

private:
    void match(const string& s, const string& p, vector<int>& matched)
    {
        int m = p.size(), n = s.size();
        if(m > n) return;
        // [0..m-1]
        int hash_p = get_hash(p, 0, m - 1);
        int hash_s = get_hash(s, 0, m - 1);
        if(hash_s == hash_p && check(s, 0, m - 1, p))
            matched.push_back(0);
        for(int i = m; i < n; ++i)
        {
            hash_s -= s[i - m] - 'a';
            hash_s += s[i] - 'a';
            if(hash_s == hash_p && check(s, i - m + 1, i, p))
                matched.push_back(i - m + 1);
        }
    }

    bool check(const string& s, int left, int right, const string& p)
    {
        // 调用方保证 m == right - left + 1
        for(int i = left; i <= right; ++i)
            if(s[i] != p[i - left])
                return false;
        return true;
    }

    int get_hash(const string& s, int left, int right)
    {
        int result = 0;
        for(int i = left; i <= right; ++i)
        {
            const char &ch = s[i];
            result = (result + (ch - 'a'));
        }
        return result;
    }
};
