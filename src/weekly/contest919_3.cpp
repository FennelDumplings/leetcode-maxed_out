#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> numsGame(vector<int>& nums) {
        int n = nums.size();
        vector<int> sums(n + 1);
        for(int i = 1; i <= n; ++i)
            sums[i] = sums[i - 1] + nums[i - 1];
        vector<int> result(n, 0);
        for(int i = 0; i < n; ++i)
        {
            // [0..i]
            int sum = sums[i + 1];
            int len = i + 1;
            // k * len 中
            //
            int avg = sum / (i + 1);
            if((i & 1) == 1)
            {
                // 偶数长度
                result[i] = min(abs(sum - (avg * 2 + 1) * (i + 1) / 2), abs(sum - (avg * 2 + 3) * (i + 1) / 2));
            }
            else
            {
                // 奇数长度
                result[i] = min(abs(sum - avg * (i + 1)), abs(sum - (avg + 1) * (i + 1)));
            }
        }
        return result;
    }
};
