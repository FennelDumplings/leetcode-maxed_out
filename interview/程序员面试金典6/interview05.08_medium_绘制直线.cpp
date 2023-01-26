// interview05.01: 绘制直线

/*
 * https://leetcode-cn.com/problems/draw-line-lcci/
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> drawLine(int length, int w, int x1, int x2, int y) {
        using ll = long long;
        int start = y * (w / 32);
        int left = x1 / 32; // 从 start 往右数 left 个
        int right = x2 / 32; // 从 start 往右数 right 个
        vector<int> result(length);
        for(int offset = left; offset <= right; ++offset)
        {
            int id = start + offset;
            // 操作 result[id]
            int l = 0;
            l = max(l, x1 - (id * 32 - start * 32));
            int r = 31;
            r = min(r, x2 - (id * 32 - start * 32));
            int k = r - l + 1;
            int num = (((ll)1 << k) - 1) << (31 - r);
            result[id] = num;
        }
        return result;
    }
};
