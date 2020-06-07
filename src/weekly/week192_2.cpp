// 20200607
// 2. 数组中的 k 个最强值

/*
 * 给你一个整数数组 arr 和一个整数 k 。
 * 设 m 为数组的中位数，只要满足下述两个前提之一，就可以判定 arr[i] 的值比 arr[j] 的值更强：
 *  |arr[i] - m| > |arr[j] - m|
 *  |arr[i] - m| == |arr[j] - m|，且 arr[i] > arr[j]
 * 请返回由数组中最强的 k 个值组成的列表。答案可以以 任意顺序 返回。
 */

/*
 * 示例 1：
 * 输入：arr = [1,2,3,4,5], k = 2
 * 输出：[5,1]
 * 解释：中位数为 3，按从强到弱顺序排序后，数组变为 [5,1,4,2,3]。最强的两个元素是 [5, 1]。[1, 5] 也是正确答案。
 * 注意，尽管 |5 - 3| == |1 - 3| ，但是 5 比 1 更强，因为 5 > 1 。
 * 示例 2：
 * 输入：arr = [1,1,3,5,5], k = 2
 * 输出：[5,5]
 * 解释：中位数为 3, 按从强到弱顺序排序后，数组变为 [5,5,1,1,3]。最强的两个元素是 [5, 5]。
 * 示例 3：
 * 输入：arr = [6,7,11,7,6,8], k = 5
 * 输出：[11,8,6,6,7]
 * 解释：中位数为 7, 按从强到弱顺序排序后，数组变为 [11,8,6,6,7,7]。
 * [11,8,6,6,7] 的任何排列都是正确答案。
 * 示例 4：
 * 输入：arr = [6,-3,7,2,11], k = 3
 * 输出：[-3,11,2]
 * 示例 5：
 * 输入：arr = [-7,22,17,3], k = 2
 * 输出：[22,17]
 */

/*
 * 提示：
 *
 * 1 <= arr.length <= 10^5
 * -10^5 <= arr[i] <= 10^5
 *  1 <= k <= arr.length
 */

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Cmp
{
    int m;
    Cmp(int m):m(m){}
    bool operator()(const int a, const int b) const
    {
        if(abs(a - m) == abs(b - m))
            return a > b;
        return abs(a - m) > abs(b - m);
    }
};

class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k) {
        int n = arr.size();
        Cmp cmp(0.0);
        sort(arr.begin(), arr.end());
        cmp.m = arr[(n - 1) / 2];
        sort(arr.begin(), arr.end(), cmp);
        return vector<int>(arr.begin(), arr.begin() + k);
    }
};
