// prob1181: Before and After Puzzle

/*
 * https://leetcode-cn.com/problems/before-and-after-puzzle/
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
        // mapping[word] := 头词为 word 的下标集合
        unordered_map<string, vector<int>> mapping;
        int n = phrases.size();
        vector<string> tail_words(n); // 尾词
        for(int i = 0; i < n; ++i)
        {
            const string &w = phrases[i];
            auto it = w.find_first_of(' ');
            string head_word;
            if(it == string::npos)
                head_word = w;
            else
                head_word = w.substr(0, it);
            mapping[head_word].push_back(i);
            it = w.find_last_of(' ');
            if(it == string::npos)
                tail_words[i] = head_word;
            else
                tail_words[i] = w.substr(it + 1);
        }
        vector<string> result;
        unordered_set<string> setting;
        for(int i = 0; i < n; ++i)
        {
            if(mapping.count(tail_words[i]) == 0)
                continue;
            for(int idx: mapping[tail_words[i]])
            {
                if(idx == i) continue;
                string item = phrases[i];
                item += phrases[idx].substr(tail_words[i].size());
                if(setting.count(item) == 0)
                {
                    result.push_back(item);
                    setting.insert(item);
                }
            }
        }
        sort(result.begin(), result.end());
        return result;
    }
};
