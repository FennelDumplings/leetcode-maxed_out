#include <vector>

using namespace std;

/*
 * 第 x 天知道，则第 [x + delay, x + forgot - 1] 天这个范围会分享
 * 那么在第 i 天时，第 [i - delay, i - forgot + 1] 天知道的人会在当前的第 i 天分享
 *
 * 第 1 天，有一个人知道
 * 从第二天开始，[2, n] 中的每一天我们都判断一次有多少人在这一天发生分享
 * 假设当前进行到第 i 天，我们只需要判断 [i - delay, i - forgot + 1] 中的每一天各有多少新增知道的人即可
 *
 * 进行到第 i 天时，i - forget 这一天的人数要清空
 */
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        const int MOD = 1e9 + 7;
        using ll = long long;
        vector<int> additional(n);
        additional[0] = 1;
        for(int i = 1; i < n; ++i)
        {
            if(i - forget >= 0)
                additional[i - forget] = 0;
            int left = i - forget + 1;
            int right = i - delay;
            if(right < 0)
                continue;
            for(int j = max(left, 0); j <= right; ++j)
            {
                additional[i] = ((ll)additional[i] + additional[j]) % MOD;
            }
        }

        int ans = 0;
        for(int x: additional)
            ans = ((ll)ans + x) % MOD;
        return ans;
    }
};

