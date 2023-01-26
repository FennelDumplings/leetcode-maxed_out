// interview16.20: T9键盘

/*
 * https://leetcode-cn.com/problems/t9-lcci/
 */

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<string> getValidT9Words(string num, vector<string>& words) {
        if(num.empty() || words.empty()) return {};
        mapping = vector<string>(10);
        setting = unordered_set<string>();
        mapping[2] = "abc";
        mapping[3] = "def";
        mapping[4] = "ghi";
        mapping[5] = "jkl";
        mapping[6] = "mno";
        mapping[7] = "pqrs";
        mapping[8] = "tuv";
        mapping[9] = "wxyz";
        int n = num.size();
        for(const string& word: words)
            if((int)word.size() == n)
                setting.insert(word);
        for(int pos = 0; pos < n; ++pos)
        {
            auto it = setting.begin();
            while(it != setting.end())
            {
                bool flag = false;
                for(const char&ch: mapping[num[pos] - '0'])
                    if((*it)[pos] == ch)
                    {
                        flag = true;
                        break;
                    }
                if(!flag)
                    it = setting.erase(it);
                else
                    ++it;
            }
        }
        vector<string> result(setting.begin(), setting.end());
        return result;
    }

private:
    vector<string> mapping;
    unordered_set<string> setting;
};

class Solution_2 {
public:
    vector<string> getValidT9Words(string num, vector<string>& words) {
        if(num.empty() || words.empty()) return {};
        mapping = vector<string>(10);
        setting = unordered_set<string>();
        mapping[2] = "abc";
        mapping[3] = "def";
        mapping[4] = "ghi";
        mapping[5] = "jkl";
        mapping[6] = "mno";
        mapping[7] = "pqrs";
        mapping[8] = "tuv";
        mapping[9] = "wxyz";
        int n = num.size();
        for(const string& word: words)
            if((int)word.size() == n)
                setting.insert(word);
        vector<string> result;
        string item;
        dfs(num, 0, result, item);
        return result;
    }

private:
    vector<string> mapping;
    unordered_set<string> setting;

    void dfs(const string& num, int pos, vector<string>& result, string& item)
    {
        int n = num.size();
        if(pos == n)
        {
            if(setting.find(item) != setting.end())
                result.push_back(item);
            return;
        }
        for(const char& ch: mapping[num[pos] - '0'])
        {
            item += ch;
            dfs(num, pos + 1, result, item);
            item.pop_back();
        }
    }
};
