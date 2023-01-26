// 面17.19: Missing Two LCCI

/*
 * 给定一个数组，包含从 1 到 N 所有的整数，但其中缺了两个数字。你能在 O(N) 时间内只用 O(1) 的空间找到它们吗？
 * 以任意顺序返回这两个数字均可。
 */
/*
 * 示例 1:
 * 输入: [1]
 * 输出: [2,3]
 * 示例 2:
 * 输入: [2,3]
 * 输出: [1,4]
 * 提示：
 * nums.length <= 30000
 */

#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> missingTwo(vector<int>& nums) {
        if(nums.empty()) return vector<int>({1, 2});
        using ll = long long;
        int N = nums.size() + 2;
        int s1 = N * (N + 1) / 2;
        int s2 = (ll)N * (N + 1) * (2 * N + 1) / 6;
        for(int num: nums)
        {
            s1 -= num;
            s2 -= (ll)num * num;
        }
        int a = 2, b = (-2) * s1, c = (s1 * s1) - s2;
        int delta = (ll)b * b - (ll)4 * a * c;
        int x = ((-b) + sqrt(delta)) / (2 * a);
        int y = s1 - x;
        return vector<int>({x, y});
    }
};
