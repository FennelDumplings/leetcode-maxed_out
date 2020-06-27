- [42. 接雨水](https://leetcode-cn.com/problems/trapping-rain-water/)
- [84. 柱状图中最大的矩形](https://leetcode-cn.com/problems/largest-rectangle-in-histogram/)
- [496. 下一个更大元素 I](https://leetcode-cn.com/problems/next-greater-element-i/)
- [739. 每日温度](https://leetcode-cn.com/problems/daily-temperatures/)
- [901. 股票价格跨度](https://leetcode-cn.com/problems/online-stock-span/)
- [907. 子数组的最小值之和](https://leetcode-cn.com/problems/sum-of-subarray-minimums/)
- [1019. 链表中的下一个更大节点](https://leetcode-cn.com/problems/next-greater-node-in-linked-list/)
- [1475. 商品折扣后的最终价格](https://leetcode-cn.com/problems/final-prices-with-a-special-discount-in-a-shop/)

以下两题为同一个思路: 第一题为基础,第二题以第一题为组件
- [456. 132模式](https://leetcode-cn.com/problems/132-pattern/)
- [255. 验证前序遍历序列二叉搜索树](https://leetcode-cn.com/problems/verify-preorder-sequence-in-binary-search-tree/) 验证前序遍历序列不含231模式

以下两题为同一个思路: 第一题为基础,第二题以第一题为组件
- [962. 最大宽度坡](https://leetcode-cn.com/problems/maximum-width-ramp/)  
**因为对起点i,右侧的 $j1 < j2$, 若 $A[j1] < A[j2]$, 则j1无用,因为对任意i,若j1为候选,则j2总会更好,因此可能的右端点为从右到左单调递增的子序列. 同理可能的 i 是从左到右的单调递减的子序列**. 先预处理出两个单调栈的元素: 可能的 i 下标和可能的 j 下标, 然后**从右往左枚举** veci, 操作 vecj.
- [1124. 表现良好的最长时间段](https://leetcode-cn.com/problems/longest-well-performing-interval/) 
1. 先预处理好前缀和数组sums, 所求区间在前缀和数组上的特性与上题相同,可以直接套用.
2. 也可以用哈希表维护,键为前缀和,值为最早出现的索引,关键引理: 当前前缀和为 sum, sum-2 出现的一定不会比sum-1更早.

以下四题均为同一思路(**单调栈维护贪心**): 当前枚举的元素先作为候选压进栈,该元素最终会不会是结果中的一员,要看后面枚举的元素会不会通过单调关系以及其它条件将他弹出去.
- [316. 去除重复字母](https://leetcode-cn.com/problems/remove-duplicate-letters/)
- [1081. 不同字符的最小子序列](https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters/)
- [402. 移掉K位数字](https://leetcode-cn.com/problems/remove-k-digits/)
- [321. 拼接最大数](https://leetcode-cn.com/problems/create-maximum-number/) 

---
