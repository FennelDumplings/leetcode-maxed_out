// interview08.07: 无重复字符串的排列组合

/*
 * https://leetcode-cn.com/problems/permutation-i-lcci/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> permutation(string S) {
        if(S.empty()) return {};
        string item;
        vector<string> result;
        int n = S.size();
        vector<bool> visited(n, false);
        dfs(S, item, result, visited);
        return result;
    }

private:
    void dfs(const string& S, string& item, vector<string>& result, vector<bool>& visited)
    {
        int n = S.size();
        if((int)item.size() == n)
        {
            result.push_back(item);
            return;
        }
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            visited[i] = true;
            item += S[i];
            dfs(S, item, result, visited);
            item.pop_back();
            visited[i] = false;
        }
    }
};
