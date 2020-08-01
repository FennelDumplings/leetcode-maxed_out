// interview10.02: 变位词组

/*
 * https://leetcode-cn.com/problems/group-anagrams-lcci/
 */

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        if(strs.empty()) return {};
        unordered_map<string, vector<string>> mapping;
        for(const string& word: strs)
        {
            string key = word;
            sort(key.begin(), key.end());
            mapping[key].push_back(word);
        }
        vector<vector<string>> result;
        for(const auto& item: mapping)
            result.push_back(item.second);
        return result;
    }
};
