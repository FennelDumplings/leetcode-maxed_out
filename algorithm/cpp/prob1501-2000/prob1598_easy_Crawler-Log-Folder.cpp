// prob1598: Crawler Log Folder

/*
 * https://leetcode-cn.com/problems/crawler-log-folder/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int minOperations(vector<string>& logs) {
        int deep = 0;
        for(const string &log: logs)
        {
            if(log == "../")
                deep = max(0, deep - 1);
            else if(log != "./")
                ++deep;
        }
        return deep;
    }
};
