#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        double r = 1e7 + 1;
        double l = 1;
        if(!check(dist, hour, r))
            return -1;
        while(r > l + EPS)
        {
            double mid = (l + r) / 2;
            if(check(dist, hour, mid))
                r = mid;
            else
                l = mid;
        }
        return ceil(l);
    }

private:
    const double EPS = 1e-9;

    bool check(const vector<int>& dist, const double hour, double v)
    {
        int n = dist.size();
        double total = 0;
        for(int i = 0; i < n - 1; ++i)
            total += ceil(dist[i] / v);
        total += dist[n - 1] / v;
        return total < hour + EPS;
    }
};
