## 分治参考
线段树隐含分治思想

## 前缀和参考
树状数组隐含前缀和思想

## 线段树和树状数组
#### 一维
- [307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/) 单点修改+区间查询
- [1476. 子矩形查询](https://leetcode-cn.com/problems/subrectangle-queries/) 区间修改+单点查询；保存操作，查询时再执行求结果
- [715. Range 模块](https://leetcode-cn.com/problems/range-module/) 平衡树也可以
- [699. 掉落的方块](https://leetcode-cn.com/problems/falling-squares/) 区间修改；平衡树区间管理 lc715

#### 二维
- [308. 二维区域和检索 - 可变](https://leetcode-cn.com/problems/range-sum-query-2d-mutable/) 单点修改，区间查询；二维BIT；二维线段树有两种写法：树套树和四叉树
- [427. 建立四叉树](https://leetcode-cn.com/problems/construct-quad-tree/)
- [558. 四叉树交集](https://leetcode-cn.com/problems/logical-or-of-two-binary-grids-represented-as-quad-trees/)
- [1274. 矩形内船只的数目](https://leetcode-cn.com/problems/number-of-ships-in-a-rectangle/) 二分分治-类似 KD 树的搜索; 四分分治-四叉树搜索

## 权值线段树和权值树状数组
- [315. 计算右侧小于当前元素的个数](https://leetcode-cn.com/problems/count-of-smaller-numbers-after-self/) 在索引数组上 CDQ 分治，归并树
- [493. 翻转对](https://leetcode-cn.com/problems/reverse-pairs/) 权值 ST / 权值 BIT / CDQ 分治
- [面试题51. 数组中的逆序对](https://leetcode-cn.com/problems/shu-zu-zhong-de-ni-xu-dui-lcof/) 权值 ST / 权值 BIT / CDQ 分治
- [327. 区间和的个数](https://leetcode-cn.com/problems/count-of-range-sum/) 权值 ST / 权值 BIT / CDQ 分治
- [1157. 子数组中占绝大多数的元素](https://leetcode-cn.com/problems/online-majority-element-in-subarray/) 主席树，分块
- [1395. 统计作战单位数](https://leetcode-cn.com/problems/count-number-of-teams/) 权值 BIT

## 线段树与扫描线
- [218. 天际线问题](https://leetcode-cn.com/problems/the-skyline-problem/) 扫描线+平衡树；线段树和分治也可以
- [391. 完美矩形](https://leetcode-cn.com/problems/perfect-rectangle/)
- [850. 矩形面积 II](https://leetcode-cn.com/problems/rectangle-area-ii/)
- [732. 我的日程安排表 III](https://leetcode-cn.com/problems/my-calendar-iii/) 扫描线+平衡树$O(N^{2})$；用离散化+线段树的话 $O(log(1e9)N)$

## 线段树优化 dp 方程中的 $dp[i] = f(max_{j=0}^{i-1}(dp[j]))$
- [300. 最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)  
- [673. 最长递增子序列的个数](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/)  

## 离散化
- [1331. 数组序号转换](https://leetcode-cn.com/problems/rank-transform-of-an-array/)

---

