// interview08.08: 有重复字符串的排列组合

/*
 * https://leetcode-cn.com/problems/permutation-ii-lcci/
 */

#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

// 哈希表
class Solution {
public:
    vector<string> permutation(string S) {
        if(S.empty()) return {};
        string item;
        vector<string> result;
        unordered_set<string> setting;
        int n = S.size();
        vector<bool> visited(n, false);
        dfs(S, item, result, visited, setting);
        return result;
    }

private:
    void dfs(const string& S, string& item, vector<string>& result, vector<bool>& visited, unordered_set<string>& setting)
    {
        int n = S.size();
        if((int)item.size() == n)
        {
            if(setting.find(item) == setting.end())
            {
                result.push_back(item);
                setting.insert(item);
                return;
            }
        }
        for(int i = 0; i < n; ++i)
        {
            if(visited[i]) continue;
            visited[i] = true;
            item += S[i];
            dfs(S, item, result, visited, setting);
            item.pop_back();
            visited[i] = false;
        }
    }
};

#include <algorithm>

class Solution_2 {
public:
    vector<string> permutation(string S) {
        if(S.empty()) return {};
        string item;
        vector<string> result;
        vector<int> mapping(52, 0);
        sort(S.begin(), S.end());
        for(const char& ch: S)
        {
            if(ch >= 'a' && ch <= 'z')
                ++mapping[ch - 'a'];
            if(ch >= 'A' && ch <= 'Z')
                ++mapping[ch - 'A' + 26];
        }
        dfs(S, item, result, mapping);
        return result;
    }

private:
    void dfs(const string& S, string& item, vector<string>& result, vector<int>& mapping)
    {
        int n = S.size();
        if((int)item.size() == n)
        {
            result.push_back(item);
            return;
        }
        for(char ch = 'a'; ch <= 'z'; ++ch)
        {
            if(mapping[ch - 'a'] == 0) continue;
            --mapping[ch - 'a'];
            item += ch;
            dfs(S, item, result, mapping);
            item.pop_back();
            ++mapping[ch - 'a'];
        }
        for(char ch = 'A'; ch <= 'Z'; ++ch)
        {
            if(mapping[ch - 'A' + 26] == 0) continue;
            --mapping[ch - 'A' + 26];
            item += ch;
            dfs(S, item, result, mapping);
            item.pop_back();
            ++mapping[ch - 'A' + 26];
        }
    }
};
