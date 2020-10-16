// prob1575: Check If String Is Transformable With Substring Sort Operations

/*
 * https://leetcode-cn.com/problems/check-if-string-is-transformable-with-substring-sort-operations/
 */

#include <string>
#include <list>
#include <vector>

using namespace std;

class Solution {
public:
    bool isTransformable(string s, string t) {
        int n = s.size();
        vector<list<int>> cnts(10);
        for(int i = 0; i < n; ++i)
            cnts[s[i] - '0'].push_back(i);
        for(int i = 0; i < n; ++i)
        {
            int cur = t[i] - '0';
            if(cnts[cur].empty())
                return false;
            int j = cnts[cur].front();
            for(int k = 0; k < cur; ++k)
                if(!cnts[k].empty() && cnts[k].front() < j)
                    return false;
            cnts[cur].erase(cnts[cur].begin());
        }
        return false;
    }
};
