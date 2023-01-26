// prob544:  Output Contest Matches

/*
 * https://leetcode-cn.com/problems/output-contest-matches/
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string findContestMatch(int n) {
        vector<string> start;
        for(int i = 1; i <= n; ++i)
            start.push_back(to_string(i));
        vector<string> result = solve(start);
        return result[0];
    }

private:
    vector<string> solve(const vector<string>& strs)
    {
        int n = strs.size();
        if(n == 1)
            return strs;
        vector<string> result(n / 2);
        for(int i = 0; i < n / 2; ++i)
        {
            result[i] = '(' + strs[i] + ',' + strs[n - 1 - i] + ')';
        }
        return solve(strs);
    }
};
