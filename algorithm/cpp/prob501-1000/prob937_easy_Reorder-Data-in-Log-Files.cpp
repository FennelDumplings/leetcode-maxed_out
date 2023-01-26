// prob937: Reorder Data in Log Files

/*
 * https://leetcode-cn.com/problems/reorder-data-in-log-files/
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Cmp
{
    bool operator()(const string& log1, const string& log2) const
    {
        int m1 = log1.size(), m2 = log2.size();
        int i1 = 0, i2 = 0;
        while(i1 < m1 && log1[i1] != ' ') ++i1;
        while(i2 < m2 && log2[i2] != ' ') ++i2;
        if(log1.substr(i1 + 1) == log2.substr(i2 + 1))
            return log1.substr(0, i1) < log2.substr(0, i2);
        return log1.substr(i1 + 1) < log2.substr(i2 + 1);
    }
};

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        if(logs.empty()) return {};
        vector<string> num_log;
        vector<string> abc_log;
        for(const string& log: logs)
        {
            int i = 0;
            int m = log.size();
            while(i < m && log[i] != ' ')
                ++i;
            ++i;
            if(i < m && log[i] >= '0' && log[i] <= '9')
                num_log.push_back(log);
            else
                abc_log.push_back(log);
        }
        sort(abc_log.begin(), abc_log.end(), Cmp());
        vector<string> result(abc_log.begin(), abc_log.end());
        result.insert(result.end(), num_log.begin(), num_log.end());
        return result;
    }
};
