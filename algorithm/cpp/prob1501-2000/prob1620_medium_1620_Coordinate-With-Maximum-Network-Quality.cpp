// prob1620: Coordinate With Maximum Network Quality

/*
 * https://leetcode-cn.com/problems/coordinate-with-maximum-network-quality/
 */

#include <vector>
#include <cmath>

using namespace std;

const double EPS = 1e-10;

int quality(int x, int y, int q, int x0, int y0, const int r)
{
    double d = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
    int ans = 0;
    if(d < r + EPS)
        ans += floor(q / (d + 1));
    return ans;
}

class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        int xmin = 51, xmax = -1, ymin = 51, ymax = -1;
        for(const vector<int>& cord: towers)
        {
            xmin = min(xmin, cord[0]);
            xmax = max(xmax, cord[0]);
            ymax = max(ymax, cord[1]);
            ymin = min(ymin, cord[1]);
        }
        int ans = 0;
        int x0 = 0, y0 = 0;
        for(int x = xmin; x <= xmax; ++x)
            for(int y = ymin; y <= ymax; ++y)
            {
                int sum = 0;
                for(const vector<int>& t: towers)
                    sum += quality(t[0], t[1], t[2], x, y, radius);
                if(sum > ans)
                {
                    ans = sum;
                    x0 = x;
                    y0 = y;
                }
            }
        return {x0, y0};
    }
};
