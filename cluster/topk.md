
## 数据流中的 topK
[480. 滑动窗口中位数](https://leetcode-cn.com/problems/sliding-window-median/)  双堆  
[703. 数据流中的第K大元素](https://leetcode-cn.com/problems/kth-largest-element-in-a-stream/)  
[295. 数据流的中位数](https://leetcode-cn.com/problems/find-median-from-data-stream/)  

#### 抽象成不断增加的数据流第 K 大
- 将某指标排序后枚举, 满足条件的候选越来越多，从越来越多的候选中选另一个指标最好的 K 个
- - [1383. 最大的团队表现值](https://leetcode-cn.com/problems/maximum-performance-of-a-team/) 最多选 k 个，最大化某指标  
- - [857. 雇佣 K 名工人的最低成本](https://leetcode-cn.com/problems/minimum-cost-to-hire-k-workers/)  选 k 个，最大化某指标

## 单串 topK
[215. 数组中的第K个最大元素](https://leetcode-cn.com/problems/kth-largest-element-in-an-array/)  

## 双串 topK
[4. 寻找两个正序数组的中位数](https://leetcode-cn.com/problems/median-of-two-sorted-arrays/)  

---

[719. 找出第 k 小的距离对](https://leetcode-cn.com/problems/find-k-th-smallest-pair-distance/)
[786. 第 K 个最小的素数分数](https://leetcode-cn.com/problems/k-th-smallest-prime-fraction/)
[440. 字典序的第K小数字](https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/)

[230. 二叉搜索树中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-bst/) 二分
[668. 乘法表中第k小的数](https://leetcode-cn.com/problems/kth-smallest-number-in-multiplication-table/) 二分
[378. 有序矩阵中第K小的元素](https://leetcode-cn.com/problems/kth-smallest-element-in-a-sorted-matrix/) 二分
