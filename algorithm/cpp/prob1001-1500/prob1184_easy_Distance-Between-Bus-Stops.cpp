// prob1184: Distance Between Bus Stops

/*
 * https://leetcode-cn.com/problems/distance-between-bus-stops/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int n = distance.size();
        int d = 0;
        for(int i = start; i != destination; i = (i + 1) % n)
            d += distance[i];
        int ans = d;
        d = 0;
        for(int i = (start - 1 + n) % n; i != (destination - 1 + n) % n; i = ((i - 1 + n) % n))
            d += distance[i];
        ans = min(ans, d);
        return ans;
    }
};
