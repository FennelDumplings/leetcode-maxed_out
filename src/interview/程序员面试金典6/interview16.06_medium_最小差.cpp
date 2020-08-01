// interview16.06: 最小差

/*
 * https://leetcode-cn.com/problems/smallest-difference-lcci/
 */

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int smallestDifference(vector<int>& a, vector<int>& b) {
        int na = a.size(), nb = b.size();
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int ia = 0, ib = 0;
        using ll = long long;
        ll ans = abs((ll)a[ia] - (ll)b[ib]);
        while(ia < na && ib < nb)
        {
            ll diff = a[ia] - b[ib];
            ans = min((ll)ans, abs(diff));
            if(diff == 0)
                return ans;
            else if(diff > 0)
                ++ib;
            else
                ++ia;
        }
        return ans;
    }
};
