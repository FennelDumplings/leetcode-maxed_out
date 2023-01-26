// prob396: Rotate Function

/*
 * https://leetcode-cn.com/problems/rotate-function/
 */

#include <vector>

using namespace std;

class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        using ll = long long;
        int n = A.size();
        vector<ll> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + A[i - 1];
        ll F = 0;
        for(int i = 0; i < n; ++i)
            F += i * A[i];
        ll ans = F;
        for(int k = 0; k < n; ++k)
        {
            ans = max(ans, F + k * sums[n - k] - (n - k) * (sums[n] - sums[n - k]));
        }
        return ans;
    }
};
