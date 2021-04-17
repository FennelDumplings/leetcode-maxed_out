// prob452: Minimum Number of Arrows to Burst Balloons

/*
 * There are a number of spherical balloons spread in two-dimensional space. For each balloon,
 * provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal,
 * y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice.
 * Start is always smaller than end. There will be at most 104 balloons.
 * An arrow can be shot up exactly vertically from different points along the x-axis.
 * A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend.
 * There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely.
 * The problem is to find the minimum number of arrows that must be shot to burst all balloons.
 */

/*
 *
 * Example:
 * Input:
 * [[10,16], [2,8], [1,6], [7,12]]
 * Output:
 * 2
 * Explanation:
 * One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if(points.empty()) return 0;
        int n = points.size();
        sort(points.begin(), points.end(), Cmp());
        int cur = points[0][1];
        int result = 1;
        for(int i = 0; i < n; ++i)
        {
            if(points[i][0] > cur)
            {
                cur = points[i][1];
                ++result;
            }
        }
        return result;
    }

private:
    struct Cmp
    {
        bool operator()(const vector<int>& vec1, const vector<int>& vec2)
        {
            if(vec1[1] == vec2[1])
                return vec1[0] < vec2[0];
            return vec1[1] < vec2[1];
        }
    };
};
