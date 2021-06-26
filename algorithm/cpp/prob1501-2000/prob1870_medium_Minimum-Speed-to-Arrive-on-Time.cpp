#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int r = 1e7 + 1;
        int l = 1;
        if(!check(dist, hour, r))
            return -1;
        while(l < r)
        {
            double mid = (l + r) / 2;
            if(check(dist, hour, mid))
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }

private:
    const double EPS = 1e-9;

    bool check(const vector<int>& dist, const double hour, int v)
    {
        int n = dist.size();
        double total = 0;
        for(int i = 0; i < n - 1; ++i)
            total += ceil(dist[i] / (double)v);
        total += dist[n - 1] / (double)v;
        return total < hour + EPS;
    }
};
