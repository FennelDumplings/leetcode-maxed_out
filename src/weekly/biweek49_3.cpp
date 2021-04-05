
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;
class Solution {
public:
    int countNicePairs(vector<int>& nums) {
        unordered_map<ll, int> mapping;
        for(int x: nums)
        {
            ll key = get_key(x);
            ++mapping[key];
        }
        int ans = 0;
        for(auto item: mapping)
        {
            int num = item.second;
            ans = (ans + num * (ll)(num - 1) / 2) % MOD;
        }
        return ans;
    }

private:
    using ll = long long;
    const int MOD = 1e9 + 7;
    ll get_key(int x)
    {
        vector<int> digits;
        while(x)
        {
            digits.push_back(x % 10);
            x /= 10;
            // digits 存的是翻转
        }
        // key = x - rev(x)
        ll key = 0;
        int m = digits.size();
        for(int i = 0; i < m; ++i)
        {
            key += (ll)(digits[i] - digits[m - 1 - i]) * pow((ll)10, (ll)i);
        }
        return key;
    }
};
