
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int breakfastNumber(vector<int>& staple, vector<int>& drinks, int x) {
        int n = staple.size();
        int m = drinks.size();
        const int MOD = 1e9 + 7;
        using ll = long long;
        sort(staple.begin(), staple.end());
        sort(drinks.begin(), drinks.end());
        int ans = 0;
        for(int a: staple)
        {
            // a + b <= x
            // b <= x - a
            if(a > x) break;
            auto it = upper_bound(drinks.begin(), drinks.end(), x - a);
            ans = (ans + (it - drinks.begin())) % MOD;
        }
        return ans;
    }
};
