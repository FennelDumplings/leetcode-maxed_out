// interview38: 字符串的排列

/*
 * https://leetcode-cn.com/problems/zi-fu-chuan-de-pai-lie-lcof/
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> permutation(string s) {
        int n = s.size();
        string item = "";
        vector<string> result;
        unordered_set<string> setting;
        vector<bool> used(n, false);
        dfs(s, 0, item, result, setting, used);
        return result;
    }

private:
    void dfs(const string& s, int pos, string& item, vector<string>& result,
            unordered_set<string>& setting, vector<bool>& used)
    {
        int n = s.size();
        if(pos == n)
        {
            if(setting.find(item) == setting.end())
            {
                result.push_back(item);
                setting.insert(item);
            }
            return;
        }

        for(int i = 0; i < n; ++i)
        {
            if(used[i]) continue;
            item += s[i];
            used[i] = true;
            dfs(s, pos + 1, item, result, setting, used);
            used[i] = false;
            item.pop_back();
        }
    }
};
