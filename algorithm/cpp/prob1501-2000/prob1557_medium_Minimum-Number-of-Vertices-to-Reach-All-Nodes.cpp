// prob1557: Minimum Number of Vertices to Reach All Nodes

/*
 * https://leetcode-cn.com/problems/minimum-number-of-vertices-to-reach-all-nodes/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) {
        vector<int> indegrees(n, 0);
        for(const vector<int> &e: edges)
            ++indegrees[e[1]];
        vector<int> result;
        for(int i = 0; i < n; ++i)
        {
            if(indegrees[i] == 0)
                result.push_back(i);
        }
        return result;
    }
};
