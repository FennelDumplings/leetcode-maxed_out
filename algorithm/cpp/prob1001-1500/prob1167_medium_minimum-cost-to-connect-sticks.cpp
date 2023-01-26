// prob1167: minimum-cost-to-connect-sticks

/*
 * 为了装修新房，你需要加工一些长度为正整数的棒材 sticks。
 * 如果要将长度分别为 X 和 Y 的两根棒材连接在一起，你需要支付 X + Y 的费用。
 * 由于施工需要，你必须将所有棒材连接成一根。
 * 返回你把所有棒材 sticks 连成一根所需要的最低费用。注意你可以任意选择棒材连接的顺序。
 */

/*
 * 示例 1：
 * 输入：sticks = [2,4,3]
 * 输出：14
 * 解释：先将 2 和 3 连接成 5，花费 5；再将 5 和 4 连接成 9；总花费为 14。
 * 示例 2：
 * 输入：sticks = [1,8,3,5]
 * 输出：30
 */

/*
 * 提示：
 * 1 <= sticks.length <= 10^4
 * 1 <= sticks[i] <= 10^4
 */

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

// 贪心法: 最小生成树
// 正确性证明：参考哈夫曼树
// 每次取最小的两个数：小顶堆出堆两次，求出和再入堆一次
class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        vector<int> heap(sticks.begin(), sticks.end());
        make_heap(heap.begin(), heap.end(), greater<int>()); // greater 生成小顶堆，默认是大顶堆
        // 访问堆头：heap.back()
        // 出堆：pop_heap(), heap.pop_back()
        // 入堆：heap.push_back(x); push_heap()
        int result = 0;;
        while(heap.size() > 1)
        {
            pop_heap(heap.begin(), heap.end(), greater<int>());
            int num1 = heap.back();
            heap.pop_back();

            pop_heap(heap.begin(), heap.end(), greater<int>());
            int num2 = heap.back();
            heap.pop_back();

            int sum = num1 + num2;
            result += sum;
            heap.push_back(sum);
            push_heap(heap.begin(), heap.end(), greater<int>());
        }
        return result;
    }
};
