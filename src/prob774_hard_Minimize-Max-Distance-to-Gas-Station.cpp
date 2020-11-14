// prob774: Minimize Max Distance to Gas Station

/*
 * https://leetcode-cn.com/problems/minimize-max-distance-to-gas-station/
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    double minmaxGasDist(vector<int>& stations, int K) {
        sort(stations.begin(), stations.end());
        int n = stations.size();
        vector<int> dist(n - 1);
        int max_d = stations[1] - stations[0];
        for(int i = 0; i < n - 1; ++i)
        {
            dist[i] = stations[i + 1] - stations[i];
            max_d = max(max_d, dist[i]);
        }
        double left = 0.0, right = max_d;
        while(left + EPS < right)
        {
            double mid = (left + right) / 2;
            int cnt = check(dist, mid);
            if(cnt > K)
                left = mid;
            else
                right = mid;
        }
        return left;
    }

private:
    const double EPS = 1e-8;

    int check(const vector<int>& dist, double mid)
    {
        int ans = 0;
        for(int d: dist)
        {
            ans += ceil(d / mid) - 1;
        }
        return ans;
    }
};
