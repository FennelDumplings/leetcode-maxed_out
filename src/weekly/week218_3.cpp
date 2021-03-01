#include <cmath>

using namespace std;

class Solution {
public:
    int concatenatedBinary(int n) {
        if(n == 1) return 1;
        using ll = long long;
        const ll MOD = 1e9 + 7;
        ll ans = 0;
        for(ll i = 1; i <= n; ++i)
        {
            ll len = log2(i) + 1;
            ans = (ans * (ll)pow(2, len)) % MOD;
            ans += i;
        }
        return ans;
    }
};
