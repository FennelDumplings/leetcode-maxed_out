// prob609: Find Duplicate File in System

/*
 * https://leetcode-cn.com/problems/find-duplicate-file-in-system/
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<vector<string>> findDuplicate(vector<string>& paths) {
        unordered_map<string, vector<string>> mapping; // content -> fold/file
        for(const string &record: paths)
        {
            auto it = record.find(' ');
            string fold = record.substr(0, it);
            while(it != string::npos)
            {
                ++it;
                auto nxt = record.find(' ', it);
                string file_info = record.substr(it, nxt - it);
                auto start = file_info.find('(');
                string file = file_info.substr(0, start);
                string c = file_info.substr(start + 1);
                c.pop_back();
                mapping[c].push_back(fold + '/' + file);
                it = nxt;
            }
        }
        vector<vector<string>> result;
        for(auto item: mapping)
        {
            if(item.second.size() > 1)
                result.push_back(item.second);
        }
        return result;
    }
};
