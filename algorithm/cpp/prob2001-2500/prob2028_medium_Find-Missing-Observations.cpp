#include <vector>

using namespace std;

class Solution {
public:
    vector<int> missingRolls(vector<int>& rolls, int mean, int n) {
        int m = rolls.size();
        int sum = 0;
        for(int x: rolls)
            sum += x;
        // n 个缺失数据，可能的 result_sum 区间为 [n, 6 * n]
        int result_sum = mean * (n + m) - sum;
        if(result_sum < n || result_sum > 6 * n)
            return {};
        vector<int> result(n);
        for(int r = n; r > 0; --r)
        {
            // 剩余 r 个数，范围 r ~ 6r
            // 1 ~ 6 中选一个数 x，填入 result[r - 1]
            // result_sum - x 的范围需要在 (r - 1) ~ 6(r - 1)
            for(int x = 1; x <= 6; ++x)
            {
                if((r - 1) <= result_sum - x && result_sum - x <= 6 * (r - 1))
                {
                    result[r - 1] = x;
                    result_sum -= x;
                    break;
                }
            }
        }
        return result;
    }
};
