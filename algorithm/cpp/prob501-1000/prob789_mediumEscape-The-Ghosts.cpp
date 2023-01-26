// prob789: Escape The Ghosts

/*
 * https://leetcode-cn.com/problems/escape-the-ghosts/
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    bool escapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        int d0 = manhattan(0, 0, target[0], target[1]);
        for(vector<int>& g: ghosts)
        {
            if(manhattan(g[0], g[1], target[0], target[1]) <= d0)
                return false;
        }
        return true;
    }

private:
    int manhattan(int x1, int y1, int x2, int y2)
    {
        return abs(x1 - x2) + abs(y1 - y2);
    }
};
