
# 双指针
- [163. 缺失的区间](https://leetcode-cn.com/problems/missing-ranges/) 双指针
- [228. 汇总区间](https://leetcode-cn.com/problems/summary-ranges/) 双指针
- [986. 区间列表的交集](https://leetcode-cn.com/problems/count-of-range-sum/)

# 贪心
- [56. 合并区间](https://leetcode-cn.com/problems/merge-intervals/) 区间合并组件，贪心排序，扫描线
- [57. 插入区间](https://leetcode-cn.com/problems/insert-interval/) 贪心排序，区间合并
- [252. 会议室](https://leetcode-cn.com/problems/meeting-rooms/) 贪心排序
- [253. 会议室 II](https://leetcode-cn.com/problems/meeting-rooms-ii/) 贪心排序，扫描线
- [435. 无重叠区间](https://leetcode-cn.com/problems/non-overlapping-intervals/) 贪心排序
- [452. 用最少数量的箭引爆气球](https://leetcode-cn.com/problems/minimum-number-of-arrows-to-burst-balloons/) 贪心排序
- [495. 提莫攻击](https://leetcode-cn.com/problems/teemo-attacking/)
- [757.  设置交集大小至少为2](https://leetcode-cn.com/problems/set-intersection-size-at-least-two/) 平衡树上维护贪心
- [616. 给字符串添加加粗标签](https://leetcode-cn.com/problems/add-bold-tag-in-string/),[758. 字符串中的加粗单词](https://leetcode-cn.com/problems/bold-words-in-string/)  枚举单词而非区间，找到所有满足条件区间(kmp求所有匹配位置)，然后区间合并
- [763. 划分字母区间](https://leetcode-cn.com/problems/partition-labels/) 先生成区间，再区间合并
- [1353. 最多可以参加的会议数目](https://leetcode-cn.com/problems/maximum-number-of-events-that-can-be-attended/) 在堆上维护贪心，枚举左端点范围，把对应的区间倒进堆里

# 平衡树
- [352. 将数据流变为多个不相交区间](https://leetcode-cn.com/problems/data-stream-as-disjoint-intervals/) 平衡树
- [436. 寻找右区间](https://leetcode-cn.com/problems/find-right-interval/) 平衡树
- [715. Range 模块](https://leetcode-cn.com/problems/range-module/) 平衡树，可以作为动态维护区间的组件
- [1288. 删除被覆盖区间](https://leetcode-cn.com/problems/remove-covered-intervals/) 平衡树，顺序遍历树中的区间时，隐含了扫描线的思想
- [729. 我的日程安排表 I](https://leetcode-cn.com/problems/my-calendar-i/)
- [699. 掉落的方块](https://leetcode-cn.com/problems/falling-squares/) 主要参考 lc715 的删除，求 r 用 lower_bound 而不是 lc715 中的 upper_bound

# 扫描线
- [56. 合并区间](https://leetcode-cn.com/problems/merge-intervals/)
- [218. 天际线问题](https://leetcode-cn.com/problems/the-skyline-problem/) 平衡树 multiset 维护 Event
- [391. 完美矩形](https://leetcode-cn.com/problems/perfect-rectangle/) Event 上保存区间，扫描线上的区间用平衡树维护区间的插入删除，保存合并后的区间(lc715)
- [1094. 拼车](https://leetcode-cn.com/problems/car-pooling/) Event 上保存区间，扫描线上的区间用平衡树维护区间的插入删除，保存原始区间
- [836. 矩形重叠](https://leetcode-cn.coMy Calendar om/problems/rectangle-overlap/) Event 上保存区间，线扫过时调用区间插入
- [731. 我的日程安排表 II](https://leetcode-cn.com/problems/my-calendar-ii/)
- [759. 员工空闲时间](https://leetcode-cn.com/problems/employee-free-time/) 
- [850. 矩形面积 II](https://leetcode-cn.com/problems/rectangle-area-ii/)
- [1229. 安排会议日程](https://leetcode-cn.com/problems/meeting-scheduler/) 
- [1272. 删除区间](https://leetcode-cn.com/problems/remove-interval/) 
- [1288. 删除被覆盖区间](https://leetcode-cn.com/problems/remove-covered-intervals/)
- [632. 最小区间](https://leetcode-cn.com/problems/smallest-range-covering-elements-from-k-lists/) 在有序 Event 数组上双指针
- [732. 我的日程安排表 III](https://leetcode-cn.com/problems/my-calendar-iii/) 扫描线+平衡树$O(N^{2})$；用线段树的话 $O(log(1e9)N)$

--- 
