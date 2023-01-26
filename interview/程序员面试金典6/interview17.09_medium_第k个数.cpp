// interview18.09: 第 k 个数

/*
 * https://leetcode-cn.com/problems/get-kth-magic-number-lcci/
 */

#include <set>

using namespace std;

class Solution {
public:
    int getKthMagicNumber(int k) {
        using ll = long long;
        set<ll> setting({1});
        ll ans = -1;
        for(int i = 1; i <= k; ++i)
        {
            auto it = setting.begin();
            ans = *it;
            setting.erase(it);
            setting.insert(ans * 3);
            setting.insert(ans * 5);
            setting.insert(ans * 7);
        }
        return ans;
    }
};


