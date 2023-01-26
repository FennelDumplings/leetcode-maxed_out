// prob1462: Course Schedule IV

/*
 * https://leetcode-cn.com/problems/course-schedule-iv/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
        vector<vector<bool> > dp(n, vector<bool>(n, false));
        for(const vector<int>& prerequisite: prerequisites)
        {
            int i = prerequisite[0], j = prerequisite[1];
            dp[i][j] = true;
        }

        for(int k = 0; k < n; ++k)
            for(int i = 0; i < n; ++i)
                for(int j = 0; j < n; ++j)
                    if(dp[i][k] && dp[k][j])
                        dp[i][j] = true;

        vector<bool> result;
        for(const vector<int>& query: queries)
        {
            int start = query[0], end = query[1];
            result.push_back(dp[start][end]);
        }
        return result;
    }
};
