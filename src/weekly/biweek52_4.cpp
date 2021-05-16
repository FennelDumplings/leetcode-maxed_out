
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        // floor(x / y) = k
        // k <= x / y < k + 1
        // ky <= x < ky + y
        // 枚举 y，得到 x 的范围，问该
        int max

    }
};
