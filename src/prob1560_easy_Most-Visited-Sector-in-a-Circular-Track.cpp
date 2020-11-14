// prob1560: Most Visited Sector in  a Circular Track

/*
 * https://leetcode-cn.com/problems/most-visited-sector-in-a-circular-track/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        int N = rounds.size();
        vector<int> result;
        if(rounds[0] == rounds[N - 1])
            return {rounds[0]};
        else if(rounds[0] < rounds[N - 1])
        {
            for(int i = rounds[0]; i <= rounds[N - 1]; ++i)
                result.push_back(i);
        }
        else
        {
            for(int i = 1; i <= rounds[N - 1]; ++i)
                result.push_back(i);
            for(int i = rounds[0]; i <= n; ++i)
            {
                result.push_back(i);
            }
        }
        return result;
    }
};
