// prob539: Minimum Time Difference

/*
 * https://leetcode-cn.com/problems/minimum-time-difference/
 */

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void get_hm(const string& s, int& h, int& m)
{
    stringstream ss;
    ss << s.substr(0, 2) + ' ';
    ss << s.substr(3);
    ss >> h;
    ss >> m;
}

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        int n = timePoints.size();
        vector<int> times(n);
        for(int i = 0; i < n; ++i)
        {
            const string &s = timePoints[i];
            int h, m;
            get_hm(s, h, m);
            times[i] = h * 60 + m;
        }
        sort(times.begin(), times.end());
        const int H = 24 * 60;
        int ans = times[0] + H - times[n - 1];
        for(int i = 0; i < n - 1; ++i)
            ans = min(ans, times[i + 1] - times[i]);
        return ans;
    }
};
