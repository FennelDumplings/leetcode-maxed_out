#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<int> pos(n);
        vector<int> amount(n);
        for(int i = 0; i < n; ++i)
        {
            pos[i] = fruits[i][0];
            amount[i] = fruits[i][1];
        }

        vector<int> sums(n + 1);
        for(int i = 0; i < n; ++i)
            sums[i + 1] = sums[i] + amount[i];

        int left = lower_bound(pos.begin(), pos.end(), startPos - k) - pos.begin();
        int right = upper_bound(pos.begin(), pos.end(), startPos + k) - pos.begin() - 1;
        if(left > right)
            return 0;
        left = max(left, 0);
        right = min(right, n - 1);

        int ans = 0;

        int j1 = upper_bound(pos.begin(), pos.end(), startPos) - pos.begin() - 1;
        for(int i = left; i < n && pos[i] <= startPos; ++i)
        {
            int j2 = upper_bound(pos.begin(), pos.end(), 2 * pos[i] + k - startPos) - pos.begin() - 1;
            int j = max(j1, j2);
            ans = max(ans, sums[j + 1] - sums[i]);
        }

        int i1 = lower_bound(pos.begin(), pos.end(), startPos) - pos.begin();
        for(int j = right; j >= 0 && pos[j] >= startPos; --j)
        {
            int i2 = lower_bound(pos.begin(), pos.end(), 2 * pos[j] - k - startPos) - pos.begin();
            int i = min(i1, i2);
            ans = max(ans, sums[j + 1] - sums[i]);
        }

        return ans;
    }
};
