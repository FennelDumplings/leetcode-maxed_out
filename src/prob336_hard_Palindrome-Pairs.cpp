// prob336: Palindrome Pairs

/*
 * https://leetcode-cn.com/problems/palindrome-pairs/
 */

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        if(words.empty()) return {};
        int n = words.size();
        if(n < 2) return {};
        unordered_map<string, int> mapping;
        for(int i = 0; i < n; ++i)
            mapping[words[i]] = i;
        vector<vector<int>> result;
        for(int i = 0; i < n; ++i)
        {
            string &word = words[i];
            int m = word.size();
            for(int l = 0; l < m; ++l)
            {
                string prefix = word.substr(0, l);
                string suffix = word.substr(l, m - l);
                bool flag_prefix = check(prefix);
                bool flag_suffix = check(suffix);
                reverse(suffix.begin(), suffix.end());
                reverse(prefix.begin(), prefix.end());
                if(flag_prefix)
                {
                    if(mapping.count(suffix) > 0 && mapping[suffix] != i)
                        result.push_back({mapping[suffix], i});
                }
                if(flag_suffix)
                {
                    if(mapping.count(prefix) > 0 && mapping[prefix] != i)
                    {
                        if(l == 0)
                        {
                            result.push_back({mapping[prefix], i});
                            result.push_back({i, mapping[prefix]});
                        }
                        else
                            result.push_back({i, mapping[prefix]});
                    }
                }
            }
        }
        return result;
    }

private:
    bool check(const string& s)
    {
        if(s.empty()) return true;
        int n = s.size();
        int l = 0, r = n - 1;
        while(l < r)
        {
            if(s[l] != s[r])
                return false;
            ++l;
            --r;
        }
        return true;
    }
};
