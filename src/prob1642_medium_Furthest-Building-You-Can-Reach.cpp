// prob1642: Furthest Building You Can Reach

/*
 * https://leetcode-cn.com/problems/furthest-building-you-can-reach/
 */


#include <vector>
using namespace std;
#include <queue>

class Solution {
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int n = heights.size();
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < n - 1; ++i)
        {
            int diff = heights[i + 1] - heights[i];
            if(diff <= 0)
                continue;
            if(ladders > 0)
            {
                --ladders;
                pq.push(diff);
            }
            else
            {
                pq.push(diff);
                if(pq.top() <= bricks)
                {
                    bricks -= pq.top();
                    pq.pop();
                }
                else
                    return i;
            }
        }
        return n - 1;
    }
};
