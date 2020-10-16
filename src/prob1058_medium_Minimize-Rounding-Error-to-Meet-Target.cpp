// prob1058: Minimize Rounding Error to Meet Target

/*
 * https://leetcode-cn.com/problems/minimize-rounding-error-to-meet-target/
 */

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Cmp
{
    bool operator()(const double& a, const double& b) const
    {
        return a - (int)a > b - (int)b;
    }
};

class Solution {
public:
    string minimizeError(vector<string>& prices, int target) {
        const double EPS = 1e-4;
        int n = prices.size();
        vector<double> ps(n);
        for(int i = 0; i < n; ++i)
        {
            const string &p = prices[i];
            stringstream ss;
            ss << p;
            ss >> ps[i];
        }
        int sum = 0;
        int integer = 0;
        for(double p: ps)
        {
            sum += (int)p;
            if(p - (int)p < EPS)
                ++integer;
        }
        int gap = target - sum; // 需要上取整的个数: gap
        if(gap < 0 || gap > n - integer) // 可以上取整的个数: n - integer
            return "-1";
        sort(ps.begin(), ps.end(), Cmp());
        double ans = 0.0;
        for(int i = 0; i < gap; ++i)
        {
            ans += ((int)ps[i] + 1) - ps[i];
        }
        for(int i = gap; i < n - integer; ++i)
        {
            ans += ps[i] - (int)ps[i];
        }
        stringstream ss;
        ss << setiosflags(ios::fixed) << setprecision(3);
        ss << ans;
        string result;
        ss >> result;
        return result;
    }
};
