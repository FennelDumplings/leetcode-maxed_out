// prob1408: String Matching in an Array

/*
 * https://leetcode-cn.com/problems/string-matching-in-an-array/
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        int n = words.size();
        vector<string> result;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(words[i].size() >= words[j].size())
                    continue;
                if(check(words[i], words[j]))
                {
                    result.push_back(words[i]);
                    break;
                }
            }
        }
        return result;
    }

private:
    bool check(string& p, string& s)
    {
        int n = s.size(), m = p.size();
        int i = 0;
        while(i <= n - m)
        {
            int j = 0;
            while(j < m && p[j] == s[i + j])
                ++j;
            if(j == m)
                return true;
            ++i;
        }
        return false;
    }
};
