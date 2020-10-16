
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maxUniqueSplit(string s) {
        int ans = 0;
        unordered_set<string> setting;
        dfs(s, 0, setting, ans);
        return ans;
    }

private:
    void dfs(const string& str, int pos, unordered_set<string>& setting, int& ans)
    {
        int n = str.size();
        if(pos == n)
        {
            ans = max(ans, (int)setting.size());
            return;
        }
        for(int j = pos; j < n; ++j)
        {
            string cand = str.substr(pos, j - pos + 1);
            if(setting.count(cand))
                continue;
            setting.insert(cand);
            dfs(str, pos + 1, setting, ans);
            setting.erase(cand);
        }
    }

};
