  
## 1、线性 DP  
### $1.1 单串 dp[i], i 是时间，位置

#### $1.1.1 最经典单串 LIS 系列：  
- [300. 最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)      
- [673. 最长递增子序列的个数](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/) LIS, len 和 cnt 各一个 dp    
- [354. 俄罗斯套娃信封问题](https://leetcode-cn.com/problems/russian-doll-envelopes) LIS    
- [960. 删列造序 III](https://leetcode-cn.com/problems/delete-columns-to-make-sorted-iii/) 自定义 LIS 中的小于
- [1048. 最长字符串链](https://leetcode-cn.com/problems/longest-string-chain/) 自定义 LIS 中的小于
- [646. 最长数对链](https://leetcode-cn.com/problems/maximum-length-of-pair-chain/) LIS 的对象是区间
- [674. 最长连续递增序列](https://leetcode-cn.com/problems/longest-continuous-increasing-subsequence/) 最长上升子串，最优解是滑动窗口，注意与最长上升子序列的区别

#### $1.1.2 最大子序列和系列： dp[i], i 是位置
- [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray)      
- [152. 乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray)      
- [918. 环形子数组的最大和](https://leetcode-cn.com/problems/maximum-sum-circular-subarray/) 环形数组的处理
- [面试题 17.24. 最大子矩阵](https://leetcode-cn.com/problems/max-submatrix-lcci/) 思路类似一维的最大子数组和
- [363. 矩形区域不超过 K 的最大数值和](https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/) 在上一题基础上加了一个 K
  
#### $1.1.3 打家劫舍系列: 不相邻子序列的最大和问题 (打家劫舍3 是树形DP)  
- [198. 打家劫舍](https://leetcode-cn.com/problems/house-robber)    
- [213. 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii) 环形数组的处理
- [740. 删除与获得点数](https://leetcode-cn.com/problems/delete-and-earn/) 在 cnt 数组上的打家劫舍    
- [1388. 3n 块披萨](https://leetcode-cn.com/problems/pizza-with-3n-slices/) 抽象成环形数组上的打家劫舍    

#### $1.1.4 变形,需要两个位置的情况: dp[i][j] 以 j, i 结尾
- [873. 最长的斐波那契子序列的长度](https://leetcode-cn.com/problems/length-of-longest-fibonacci-subsequence/) dp[i][j]:= 以 j, i 结尾，转移时在 [0..j] 中找满足条件的 k 这一步可以二分或哈希表
- [1027. 最长等差数列](https://leetcode-cn.com/problems/longest-arithmetic-sequence/) dp[i][j]:= 以 j, i 结尾，转移时在 [0..j] 中找满足条件的 k 这一步用哈希表，键为数组值，值为保存下标的平衡树

#### $1.1.5 与其它算法配合
- [1055. 形成字符串的最短路径](https://leetcode-cn.com/problems/shortest-way-to-form-string/) DP + 二分，贪心
- [368. 最大整除子集](https://leetcode-cn.com/problems/largest-divisible-subset/) 先对数组排序

#### $1.1.6 其它单串 dp[i] 问题
- [32. 最长有效括号](https://leetcode-cn.com/problems/longest-valid-parentheses/)
- [413. 等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/)
- [91. 解码方法](https://leetcode-cn.com/problems/decode-ways/)
- [132. 分割回文串 II](https://leetcode-cn.com/problems/palindrome-partitioning-ii/)
- [338. 比特位计数](https://leetcode-cn.com/problems/counting-bits/)
- [801. 使序列递增的最小交换次数](https://leetcode-cn.com/problems/minimum-swaps-to-make-sequences-increasing/)  
- [871. 最低加油次数](https://leetcode-cn.com/problems/minimum-number-of-refueling-stops/)
- [583. 两个字符串的删除操作](https://leetcode-cn.com/problems/delete-operation-for-two-strings/)  
- [978. 最长湍流子数组](https://leetcode-cn.com/problems/longest-turbulent-subarray/)
- [656. 金币路径](https://leetcode-cn.com/problems/coin-path/)
- [1024. 视频拼接](https://leetcode-cn.com/problems/video-stitching/)
- [639. 解码方法 2](https://leetcode-cn.com/problems/decode-ways-ii/)

### $1.2 双串 dp[i][j], i 是第一串的时间，位置；j 是第二串的时间，位置
#### $1.2.1 最经典双串 LCS 系列：  
- [1143. 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence)    
- [1092. 最短公共超序列](https://leetcode-cn.com/problems/shortest-common-supersequence/) 动态规划求出最优解后再求对应的路径
- [712. 两个字符串的最小ASCII删除和](https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/) LCS，len 和 ascii 各一个 dp    
- [718. 最长重复子数组](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/submissions/) 最长公共子串，最优解但是滑动窗口，注意与最长公共子序列的区别


#### $1.2.2 字符串匹配系列  
- [72. 编辑距离](https://leetcode-cn.com/problems/edit-distance)    
- [44. 通配符匹配](https://leetcode-cn.com/problems/wildcard-matching)    
- [10. 正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching)    

#### $1.2.3 其它双串 dp[i][j] 问题
- [97. 交错字符串](https://leetcode-cn.com/problems/interleaving-string/)  
- [115. 不同的子序列](https://leetcode-cn.com/problems/distinct-subsequences/)  
- [727. 最小窗口子序列](https://leetcode-cn.com/problems/minimum-window-subsequence/)  
  
### $1.3 单串 dp[i][k]，i 是位置，时间，高度等；k 是长度，个数，次数，颜色等，k 上可能有二分，贪心等  
- [813. 最大平均值和的分组](https://leetcode-cn.com/problems/largest-sum-of-averages/) k 是个数
- [887. 鸡蛋掉落](https://leetcode-cn.com/problems/super-egg-drop)  k 是次数，k 上有二分    
- [256. 粉刷房子](https://leetcode-cn.com/problems/paint-house/) k 是颜色
- [265. 粉刷房子 II](https://leetcode-cn.com/problems/paint-house-ii/) k 是颜色
- [975. 奇偶跳](https://leetcode-cn.com/problems/odd-even-jump/) k 表示当前的奇偶状态
- [403. 青蛙过河](https://leetcode-cn.com/problems/frog-jump/) k 表示上一步的跳的步数
- [1478. 安排邮筒](https://leetcode-cn.com/problems/allocate-mailboxes/) k 是个数, 前缀和维护状态转移时的查询
- [1230. 抛掷硬币](https://leetcode-cn.com/problems/toss-strange-coins/) k 是个数
- [410. 分割数组的最大值](https://leetcode-cn.com/problems/split-array-largest-sum/) k 是份数
- [1473. 给房子涂色 III](https://leetcode-cn.com/problems/paint-house-iii/) 有两个指标 k 颜色; t 街区数
- [446. 等差数列划分 II - 子序列](https://leetcode-cn.com/problems/arithmetic-slices-ii-subsequence/) k 是公差
- [903. DI 序列的有效排列](https://leetcode-cn.com/problems/valid-permutations-for-di-sequence/) k 是满足一定条件的元素个数
- [983. 最低票价](https://leetcode-cn.com/problems/minimum-cost-for-tickets/) k 是种类
- [487. 最大连续1的个数 II](https://leetcode-cn.com/problems/max-consecutive-ones-ii/) k 为是否使用操作
- [956. 最高的广告牌](https://leetcode-cn.com/problems/tallest-billboard/) k 是高度差

#### $1.3.1 股票系列: dp[i][k][state] i 是时间，k 是次数，state 是状态机(在某一个位置或者时刻可以选择多种状态)
- [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock)    
- [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii)    
- [123. 买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii)    
- [188. 买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv)    
- [309. 最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown)    
- [714. 买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee)    
  
### $1.4 双串 dp[i][j][k]
- **[87. 扰乱字符串](https://leetcode-cn.com/problems/scramble-string/)**


### $1.5 矩阵 dp[i][j]  (i, j) 共同表示位置
- [120. 三角形最小路径和](https://leetcode-cn.com/problems/triangle)    
- [64. 最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)  
- [174. 地下城游戏](https://leetcode-cn.com/problems/dungeon-game/)  
- [931. 下降路径最小和](https://leetcode-cn.com/problems/minimum-falling-path-sum/)
- [221. 最大正方形](https://leetcode-cn.com/problems/maximal-square/)
- [1289. 下降路径最小和  II](https://leetcode-cn.com/problems/minimum-falling-path-sum-ii/)


#### 变形:两个位置的情况 dp[位置1][位置2]
原始方程是四维, dp[i1][j1][i2][j2], 如果有一个约束条件，可以 dp[i1][i2][k]
- [741. 摘樱桃](https://leetcode-cn.com/problems/cherry-pickup/)  dp[i1][i2][k] k 为步数，另：流量为 2 的最大费用最大流，每个点拆成费用 i 和费用 0 的边
- [ ] [1463. 摘樱桃 II](https://leetcode-cn.com/problems/cherry-pickup-ii/) dp[i1][i2][level] level 为层数

### $1.6 矩阵 dp[i][j][k], (i, j) 为位置，k 为次数，长度等指标
- [85. 最大矩形](https://leetcode-cn.com/problems/maximal-rectangle/) k 是
- [363. 矩形区域不超过 K 的最大数值和](https://leetcode-cn.com/problems/max-sum-of-rectangle-no-larger-than-k/) k 为宽度
- [面试题 17.24. 最大子矩阵](https://leetcode-cn.com/problems/max-submatrix-lcci/) 思路类似一维的最大子数组和
- [1444. 切披萨的方案数](https://leetcode-cn.com/problems/number-of-ways-of-cutting-a-pizza/) 需要二维前缀和判断两个状态之间能否转移
- [688. “马”在棋盘上的概率](https://leetcode-cn.com/problems/knight-probability-in-chessboard/) k 表示剩余次数
- [750. 角矩形的数量](https://leetcode-cn.com/problems/number-of-corner-rectangles/) k 是底边左端点
- [764. 最大加号标志](https://leetcode-cn.com/problems/largest-plus-sign/) k 延伸方向, 共 4 个

#### $1.7 无串线性 dp
- [650. 只有两个键的键盘](https://leetcode-cn.com/problems/2-keys-keyboard/) 有数学法
- [651. 4键键盘](https://leetcode-cn.com/problems/4-keys-keyboard/) 需要二维状态 dp[i][k], k 是紧跟着的粘贴次数，有数学法
- [264. 丑数 II](https://leetcode-cn.com/problems/ugly-number-ii/) 
- **[279. 完全平方数](https://leetcode-cn.com/problems/perfect-squares/)** 有数学法
- [343. 整数拆分](https://leetcode-cn.com/problems/integer-break/)
- [1335. 工作计划的最低难度](https://leetcode-cn.com/problems/minimum-difficulty-of-a-job-schedule/)
- [920. 播放列表的数量](https://leetcode-cn.com/problems/number-of-music-playlists/) 有数学法
- [629. K个逆序对数组](https://leetcode-cn.com/problems/k-inverse-pairs-array/)

---

#### 2、区间 DP  
- [5. 最长回文子串](https://leetcode-cn.com/problems/longest-palindromic-substring/)
- [647. 回文子串](https://leetcode-cn.com/problems/palindromic-substrings/)
- [312. 戳气球](https://leetcode-cn.com/problems/burst-balloons)    
- [546. 移除盒子](https://leetcode-cn.com/problems/remove-boxes/) 戳气球升级版，[i][j] 基础上加了一维 k 状态，k 是 j 右侧与 j 相同的元素个数, 记忆化
- [486. 预测赢家](https://leetcode-cn.com/problems/predict-the-winner/)
- [516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence)    
- [1000. 合并石头的最低成本](https://leetcode-cn.com/problems/minimum-cost-to-merge-stones/)
- [1147. 段式回文](https://leetcode-cn.com/problems/longest-chunked-palindrome-decomposition/)
- [730. 统计不同回文子字符串](https://leetcode-cn.com/problems/count-different-palindromic-subsequences)    
- [1039. 多边形三角剖分的最低得分](https://leetcode-cn.com/problems/minimum-score-triangulation-of-polygon)    
- [664. 奇怪的打印机](https://leetcode-cn.com/problems/strange-printer)    
- [1312. 让字符串成为回文串的最少插入次数](https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/) 最长回文子序列
- [471. 编码最短长度的字符串](https://leetcode-cn.com/problems/encode-string-with-shortest-length/)
  
#### 3、背包 DP  
组合问题(求方案数)  
`dp[i] = dp[i] + dp[i - num]`
- [377. 组合总和 Ⅳ](https://leetcode-cn.com/problems/combination-sum-iv/) 顺序不同的序列被视作不同的组合  
- [494. 目标和 (01背包-求方案数)](https://leetcode-cn.com/problems/target-sum)    
- [518. 零钱兑换 II (完全背包-求方案数)](https://leetcode-cn.com/problems/coin-change-2)    
- [879. 盈利计划(01背包-求方案数)](https://leetcode-cn.com/problems/profitable-schemes/) 总价值有要求：有下限

恰好取到背包容量  
`dp[i] = dp[i] or dp[i - num]`  
- [416. 分割等和子集 (01背包-要求恰好取到背包容量)](https://leetcode-cn.com/problems/partition-equal-subset-sum)    

最值问题  
`dp[i] = min/max(dp[i], dp[i - num] + 1)`  
- [322. 零钱兑换 (完全背包)](https://leetcode-cn.com/problems/coin-change)    
- [474. 一和零 (二维费用背包)](https://leetcode-cn.com/problems/ones-and-zeroes)    
- [1049. 最后一块石头的重量 II](https://leetcode-cn.com/problems/last-stone-weight-ii/) 转换为01背包问题，使得背包剩余容量最小
- - 传统做法：
- - - dp[i][j] := 在面对第 i 件物品，且背包容量为 j 时所能获得的**最大价值**
- - - dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]] + w[i]); 第一项是不选 i, 第二项是选 i(j - v[i] >= 0)
- - 使得背包容量最小的做法: dp[i][j] := 在面对第 i 件物品, 背包容量为 j 时，能取到的**最大体积**
- - - dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - v[i]]); 第一项是不选 i, 第二项是选 i(j - stones[i] >= 0)
  
步骤：  
1. 分析是否为背包问题。  
2. 是以上三种背包问题中的哪一种。  
3. 是0-1背包问题还是完全背包问题。也就是题目给的nums数组中的元素是否可以重复使用。  
4. 如果是组合问题，是否需要考虑元素之间的顺序。需要考虑顺序有顺序的解法，不需要考虑顺序又有对应的解法。  
  
#### 4、树形 DP  
- [124. 二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum)    
- [1245. 树的直径 (邻接表上的树形DP)](https://leetcode-cn.com/problems/tree-diameter)    
- [543. 二叉树的直径](https://leetcode-cn.com/problems/diameter-of-binary-tree)    
- [333. 最大 BST 子树](https://leetcode-cn.com/problems/largest-bst-subtree)    
- [337. 打家劫舍 III](https://leetcode-cn.com/problems/house-robber-iii)    
- [1373. 二叉搜索子树的最大键值和](https://leetcode-cn.com/problems/maximum-sum-bst-in-binary-tree/)
- [1372. 二叉树中的最长交错路径](https://leetcode-cn.com/problems/longest-zigzag-path-in-a-binary-tree/)    
- [968. 监控二叉树](https://leetcode-cn.com/problems/binary-tree-cameras/)  
- [1273. 删除树节点](https://leetcode-cn.com/problems/delete-tree-nodes/)  
>dp[i] := 节点 i 去掉和为 0 的子树后的子树节点数  
>sum[i] := 表示节点i的子树和  
>dp[i] = dp[i.left] + dp[i.right] + 1  
>sum[i] = sum[i.left] + sum[i.right] + val(i);  

#### 5、状态压缩 DP  
- [351. 安卓系统手势解锁](https://leetcode-cn.com/problems/android-unlock-patterns/)
- [464. 我能赢吗](https://leetcode-cn.com/problems/can-i-win)    
- [980. 不同路径 III](https://leetcode-cn.com/problems/unique-paths-iii/) 状态压缩DP+记忆化
- [698. 划分为k个相等的子集](https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/) 状态压缩DP+记忆化
- [847. 访问所有节点的最短路径](https://leetcode-cn.com/problems/shortest-path-visiting-all-nodes/) Floyd + 状态压缩DP 求最短哈密顿路
- [943. 最短超级串](https://leetcode-cn.com/problems/find-the-shortest-superstring/) 状态压缩DP + DP过程记录路径
- [526. 优美的排列](https://leetcode-cn.com/problems/beautiful-arrangement)    
- [935. 骑士拨号器](https://leetcode-cn.com/problems/knight-dialer)    
- [1349. 参加考试的最大学生数](https://leetcode-cn.com/problems/maximum-students-taking-exam)    
- [638. 大礼包](https://leetcode-cn.com/problems/shopping-offers/)
- [691. 贴纸拼词](https://leetcode-cn.com/problems/stickers-to-spell-word/)
- [982. 按位与为零的三元组](https://leetcode-cn.com/problems/triples-with-bitwise-and-equal-to-zero/)

#### 6、数位 DP  
#### 满足某些条件的数字个数
- [902. 最大为 N 的数字组合](https://leetcode-cn.com/problems/numbers-at-most-n-given-digit-set/)
- [248. 中心对称数 III](https://leetcode-cn.com/problems/strobogrammatic-number-iii/)
- [357. 计算各个位数不同的数字个数](https://leetcode-cn.com/problems/count-numbers-with-unique-digits/)
- [1088. 易混淆数 II](https://leetcode-cn.com/problems/confusing-number-ii/)
- [1012. 至少有 1 位重复的数字](https://leetcode-cn.com/problems/numbers-with-repeated-digits/)
- [600. 不含连续1的非负整数](https://leetcode-cn.com/problems/non-negative-integers-without-consecutive-ones/)
- [ ] [1397. 找到所有好字符串](https://leetcode-cn.com/problems/find-all-good-strings/) 根据字符串的字典序，本题具有**给定下界 l 和上界 r，求 [l, r] 之间满足某一要求的元素个数**的形式。

#### 求总的贡献
- [233. 数字 1 的个数](https://leetcode-cn.com/problems/number-of-digit-one/)
- [1067. 范围内的数字计数](https://leetcode-cn.com/problems/digit-count-in-range/)
  
#### 7、计数问题  
计数是组合数学的重要内容。不考虑用母函数等手段求解析解的化，计数问题一般有两种做法
1. 找到组合数公式，然后用 DP 的方式求组合数  
2. 找到递归关系，然后以 DP 的方式求这个递推关系，如果是线性递推关系，可以用矩阵快速幂加速

以卡特兰数为例，
1. 组合数公式: $C_{n} = \dbinom{2n}{n} - \dbinom{2n}{n - 1} = \frac{1}{n + 1}\dbinom{2n}{n} = \prod_{k=2}^{n}\frac{n + k}{k}$
2. 递推式: $C_{n} = \sum_{i=0}^{N-1}C_{i}C_{n-i-1}$  
  
路径问题(组合数学中的格路模型，每个格路模型都有一个等价的放球模型)：  
- [62. 不同路径](https://leetcode-cn.com/problems/unique-paths)    
- [63. 不同路径 II](https://leetcode-cn.com/problems/unique-paths-ii)    
  
卡特兰数：    
- [96. 不同的二叉搜索树 (卡特兰数)](https://leetcode-cn.com/problems/unique-binary-search-trees)   
- [1259. 不相交的握手 (卢卡斯定理求大组合数模质数)](https://leetcode-cn.com/problems/handshakes-that-dont-cross) 卢卡斯定理求大组合数  
  
铺砖问题：  
- [790. 多米诺和托米诺平铺](https://leetcode-cn.com/problems/domino-and-tromino-tiling/)    
  
斐波那契：
- [70. 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs)    
- [746. 使用最小花费爬楼梯](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)
- [509. 斐波那契数](https://leetcode-cn.com/problems/fibonacci-number)    
- [1137. 第 N 个泰波那契数](https://leetcode-cn.com/problems/n-th-tribonacci-number)    
- [面试题10- I. 斐波那契数列](https://leetcode-cn.com/problems/fei-bo-na-qi-shu-lie-lcof/)

隐晦的递推关系: 
- [935. 骑士拨号器](https://leetcode-cn.com/problems/knight-dialer)    
- [418. 屏幕可显示句子的数量](https://leetcode-cn.com/problems/sentence-screen-fitting/)  可以通过模拟找循环节
- [957. N 天后的牢房](https://leetcode-cn.com/problems/prison-cells-after-n-days) 可以通过模拟找循环节
- [276. 栅栏涂色](https://leetcode-cn.com/problems/paint-fence/)  
- [1155. 掷骰子的N种方法](https://leetcode-cn.com/problems/number-of-dice-rolls-with-target-sum/)
- [552. 学生出勤记录 II](https://leetcode-cn.com/problems/student-attendance-record-ii/)
  
#### 9、概率型 DP  
求概率，求数学期望  
- [808. 分汤](https://leetcode-cn.com/problems/soup-servings)    
- [837. 新21点](https://leetcode-cn.com/problems/new-21-game)    
- [1230. 抛掷硬币](https://leetcode-cn.com/problems/toss-strange-coins/) k 是个数
- [688. “马”在棋盘上的概率](https://leetcode-cn.com/problems/knight-probability-in-chessboard/) 用全概率公式进行状态转移
  
#### 10、博弈型 DP  
策梅洛定理，SG 定理，minimax  

- [375. 猜数字大小 II](https://leetcode-cn.com/problems/guess-number-higher-or-lower-ii/)
- [486. 预测赢家](https://leetcode-cn.com/problems/predict-the-winner/)
- [464. 我能赢吗](https://leetcode-cn.com/problems/can-i-win)    
- [1025. 除数博弈](https://leetcode-cn.com/problems/divisor-game/)
- [913. 猫和老鼠](https://leetcode-cn.com/problems/cat-and-mouse/)
  
##### 翻转游戏  
- [293. 翻转游戏](https://leetcode-cn.com/problems/flip-game)    
- [294. 翻转游戏 II](https://leetcode-cn.com/problems/flip-game-ii)    
  
#####  Nim游戏  
- [292. Nim 游戏](https://leetcode-cn.com/problems/nim-game)    

##### 石子游戏  
- [877. 石子游戏](https://leetcode-cn.com/problems/stone-game)    
- [1140. 石子游戏 II](https://leetcode-cn.com/problems/stone-game-ii/)    
  
##### 井字游戏  
- [348. 判定井字棋胜负](https://leetcode-cn.com/problems/design-tic-tac-toe)    
- [794. 有效的井字游戏](https://leetcode-cn.com/problems/valid-tic-tac-toe-state)    
- [1275. 找出井字棋的获胜者](https://leetcode-cn.com/problems/find-winner-on-a-tic-tac-toe-game)    
  
#### 11、记忆化搜索  
本质是 dfs + 记忆化，用在状态的转移方向不确定的情况  
- [329. 矩阵中的最长递增路径](https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix) 另：二维的剥洋葱DP，即先通过拓扑排序把顺序找到
- [576. 出界的路径数](https://leetcode-cn.com/problems/out-of-boundary-paths)    
- [139. 单词拆分](https://leetcode-cn.com/problems/word-break/) 单串 dp[i]
- [140. 单词拆分 II](https://leetcode-cn.com/problems/word-break-ii/) 单串 dp[i]
- [472. 连接词](https://leetcode-cn.com/problems/concatenated-words/) 140题变形
- [818. 赛车](https://leetcode-cn.com/problems/race-car/) 单串 dp[i]
- [980. 不同路径 III](https://leetcode-cn.com/problems/unique-paths-iii/) 状态压缩DP+记忆化
- [638. 大礼包](https://leetcode-cn.com/problems/shopping-offers/)
- [688. “马”在棋盘上的概率](https://leetcode-cn.com/problems/knight-probability-in-chessboard/) k 表示剩余次数
- [514. 自由之路](https://leetcode-cn.com/problems/freedom-trail/) 双串 dp[i][j]
- [546. 移除盒子](https://leetcode-cn.com/problems/remove-boxes/) 戳气球升级版，[i][j] 基础上加了一维 k 状态，k 是 j 右侧与 j 相同的元素个数, 记忆化

#### 12、DAG
- [568. 最大休假天数](https://leetcode-cn.com/problems/maximum-vacation-days/) HMM 前向传播
- [1048. 最长字符串链](https://leetcode-cn.com/problems/longest-string-chain/) DAG 最长路

#### 13、其它
- [466. 统计重复个数](https://leetcode-cn.com/problems/count-the-repetitions/) 倍增优化 DP, 序列自动机


---

[920. 播放列表的数量](https://leetcode-cn.com/problems/number-of-music-playlists/)
[940. 不同的子序列 II](https://leetcode-cn.com/problems/distinct-subsequences-ii/)
[964. 表示数字的最少运算符](https://leetcode-cn.com/problems/least-operators-to-express-number/)
[1058. 最小化舍入误差以满足目标](https://leetcode-cn.com/problems/minimize-rounding-error-to-meet-target/)
[1066. 校园自行车分配 II](https://leetcode-cn.com/problems/campus-bikes-ii/)
[1074. 元素和为目标值的子矩阵数量](https://leetcode-cn.com/problems/number-of-submatrices-that-sum-to-target/) 思路类似求和为K的子数组的数量
[1105. 填充书架](https://leetcode-cn.com/problems/filling-bookcase-shelves/)
[1125. 最小的必要团队](https://leetcode-cn.com/problems/smallest-sufficient-team/)
[1130. 叶值的最小代价生成树](https://leetcode-cn.com/problems/minimum-cost-tree-from-leaf-values/)
[1139. 最大的以 1 为边界的正方形](https://leetcode-cn.com/problems/largest-1-bordered-square/)
[1140. 石子游戏 II](https://leetcode-cn.com/problems/stone-game-ii/)
[1186. 删除一次得到子数组最大和](https://leetcode-cn.com/problems/maximum-subarray-sum-with-one-deletion/)
[1187. 使数组严格递增](https://leetcode-cn.com/problems/make-array-strictly-increasing/)
[1191. K 次串联后最大子数组之和](https://leetcode-cn.com/problems/k-concatenation-maximum-sum/)
[1199. 建造街区的最短时间](https://leetcode-cn.com/problems/minimum-time-to-build-blocks/)
[1216. 验证回文字符串 III](https://leetcode-cn.com/problems/valid-palindrome-iii/)
[1218. 最长定差子序列](https://leetcode-cn.com/problems/longest-arithmetic-subsequence-of-given-difference/)
[1220. 统计元音字母序列的数目](https://leetcode-cn.com/problems/count-vowels-permutation/)
[1223. 掷骰子模拟](https://leetcode-cn.com/problems/dice-roll-simulation/)
[1227. 飞机座位分配概率](https://leetcode-cn.com/problems/airplane-seat-assignment-probability/)
[1235. 规划兼职工作](https://leetcode-cn.com/problems/maximum-profit-in-job-scheduling/)
[1240. 铺瓷砖](https://leetcode-cn.com/problems/tiling-a-rectangle-with-the-fewest-squares/)
[1246. 删除回文子数组](https://leetcode-cn.com/problems/palindrome-removal/)
[1262. 可被三整除的最大和](https://leetcode-cn.com/problems/greatest-sum-divisible-by-three/)
[1269. 停在原地的方案数](https://leetcode-cn.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/)
[1277. 统计全为 1 的正方形子矩阵](https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/)
[1278. 分割回文串 III](https://leetcode-cn.com/problems/palindrome-partitioning-iii/)
[1301. 最大得分的路径数目](https://leetcode-cn.com/problems/number-of-paths-with-max-score/)
[1320. 二指输入的的最小距离](https://leetcode-cn.com/problems/minimum-distance-to-type-a-word-using-two-fingers/)
[1339. 分裂二叉树的最大乘积](https://leetcode-cn.com/problems/maximum-product-of-splitted-binary-tree/)
[1340. 跳跃游戏 V](https://leetcode-cn.com/problems/jump-game-v/)
[1359. 有效的快递序列数目](https://leetcode-cn.com/problems/count-all-valid-pickup-and-delivery-options/)
[1363. 形成三的最大倍数](https://leetcode-cn.com/problems/largest-multiple-of-three/)
[1402. 做菜顺序](https://leetcode-cn.com/problems/reducing-dishes/)
[1405. 最长快乐字符串](https://leetcode-cn.com/problems/longest-happy-string/)
[1406. 石子游戏 III](https://leetcode-cn.com/problems/stone-game-iii/)
[1411. 给 N x 3 网格图涂色的方案数](https://leetcode-cn.com/problems/number-of-ways-to-paint-n-x-3-grid/)
[1416. 恢复数组](https://leetcode-cn.com/problems/restore-the-array/)
[1420. 生成数组](https://leetcode-cn.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/)
[1423. 可获得的最大点数](https://leetcode-cn.com/problems/maximum-points-you-can-obtain-from-cards/)
[1425. 带限制的子序列和](https://leetcode-cn.com/problems/constrained-subsequence-sum/)
[1434. 每个人戴不同帽子的方案数](https://leetcode-cn.com/problems/number-of-ways-to-wear-different-hats-to-each-other/)
[1449. 数位成本和为目标值的最大数字](https://leetcode-cn.com/problems/form-largest-integer-with-digits-that-add-up-to-target/)
[1458. 两个子序列的最大点积](https://leetcode-cn.com/problems/max-dot-product-of-two-subsequences/)
[1467. 两个盒子中球的颜色数相同的概率](https://leetcode-cn.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/)

prob1 ~ prob1473
