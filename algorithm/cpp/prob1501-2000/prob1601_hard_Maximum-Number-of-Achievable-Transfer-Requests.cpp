// prob1601: Maximum Number of Achievable Transfer Requests

/*
 * https://leetcode-cn.com/problems/maximum-number-of-achievable-transfer-requests/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        vector<int> indegrees(n), outdegrees(n);
        int m = requests.size();
        int ans = 0;
        for(int state = 0; state < (1 << m); ++state)
        {
            indegrees.assign(n, 0);
            outdegrees.assign(n, 0);
            for(int i = 0; i < m; ++i)
            {
                if(state >> i & 1)
                {
                    ++indegrees[requests[i][1]];
                    ++outdegrees[requests[i][0]];
                }
            }
            bool flag = true;
            for(int i = 0; i < n; ++i)
                if(indegrees[i] != outdegrees[i])
                {
                    flag = false;
                    break;
                }
            if(flag)
            {
                int len = 0;
                int s = state;
                while(s)
                {
                    if(s & 1)
                        ++len;
                    s >>= 1;
                }
                ans = max(ans, len);
            }
        }
        return ans;
    }
};
