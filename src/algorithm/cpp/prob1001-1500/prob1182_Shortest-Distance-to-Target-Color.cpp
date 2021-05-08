// prob1182: Shortest Distance to Target Color

/*
 * https://leetcode-cn.com/problems/shortest-distance-to-target-color/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();
        vector<vector<int>> mapping(4);
        for(int i = 0; i < n; ++i)
        {
            mapping[colors[i]].push_back(i);
        }
        int m = queries.size();
        vector<int> result(m, n + 1);
        for(int i = 0; i < m; ++i)
        {
            int start = queries[i][0];
            int target = queries[i][1];
            if(mapping[target].empty())
            {
                result[i] = -1;
                continue;
            }
            auto it = lower_bound(mapping[target].begin(), mapping[target].end(), start);
            if(it != mapping[target].end())
                result[i] = *it - start;
            if(it != mapping[target].begin())
                result[i] = min(result[i], start - *(prev(it)));
        }
        return result;
    }
};
