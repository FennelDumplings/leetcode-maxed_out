// prob997: Find the Town Judge

/*
 * https://leetcode-cn.com/problems/find-the-town-judge/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        vector<int> indegrees(N + 1);
        vector<int> outdegrees(N + 1);
        for(vector<int> &e: trust)
        {
            ++indegrees[e[1]];
            ++outdegrees[e[0]];
        }
        for(int i = 1; i <= N; ++i)
        {
            if(indegrees[i] == N - 1 && outdegrees[i] == 0)
                return i;
        }
        return -1;
    }
};
