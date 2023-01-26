// prob1011: Capacity To Ship Packages Within D Days

/*
 * https://leetcode-cn.com/problems/capacity-to-ship-packages-within-d-days/
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int shipWithinDays(vector<int>& weights, int D) {
        int n = weights.size();
        vector<int> sums(n + 1);
        int maxx = 0;
        for(int i = 1; i <= n; ++i)
        {
            maxx = max(maxx, weights[i - 1]);
            sums[i] = sums[i - 1] + weights[i - 1];
        }
        int left = maxx, right = sums[n];
        while(left < right)
        {
            int mid = (left + right) / 2;
            int T = check(sums, mid);
            if(T > D)
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

private:
    int check(const vector<int>& sums, int mid)
    {
        int ans = 0;
        auto it = sums.begin() + 1;
        while(it != sums.end())
        {
            int target = *(prev(it)) + mid;
            it = upper_bound(it, sums.end(), target);
            ++ans;
        }
        return ans;
    }
};
