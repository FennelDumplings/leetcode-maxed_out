  
## 1、线性 DP  
### $1.1 单串 dp[i], i 是时间，位置
#### $1.1.1 最经典单串 LIS 系列：  
- [300. 最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)      
- [673. 最长递增子序列的个数](https://leetcode-cn.com/problems/number-of-longest-increasing-subsequence/) LIS, len 和 cnt 各一个 dp    
- [354. 俄罗斯套娃信封问题](https://leetcode-cn.com/problems/russian-doll-envelopes) LIS    

#### $1.1.2 最大子序列和系列： dp[i], i 是位置
- [53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray)      
- [152. 乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray)      
- [918. 环形子数组的最大和](https://leetcode-cn.com/problems/maximum-sum-circular-subarray/) 环形数组的处理
  
#### $1.1.3 打家劫舍系列: 不相邻子序列的最大和问题 (打家劫舍3 是树形DP)  
- [198. 打家劫舍](https://leetcode-cn.com/problems/house-robber)    
- [213. 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii) 环形数组的处理
- [740. 删除与获得点数](https://leetcode-cn.com/problems/delete-and-earn/) 在 cnt 数组上的打家劫舍    
- [1388. 3n 块披萨](https://leetcode-cn.com/problems/pizza-with-3n-slices/) 抽象成环形数组上的打家劫舍    

### $1.2 双串 dp[i][j], i 是第一串的时间，位置；j 是第二串的时间，位置
#### $1.2.1 最经典双串 LCS 系列：  
- [1143. 最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence)    
- [712. 两个字符串的最小ASCII删除和](https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/) LCS，len 和 ascii 各一个 dp    

#### $1.2.2 字符串匹配系列  
- [72. 编辑距离](https://leetcode-cn.com/problems/edit-distance)    
- [44. 通配符匹配](https://leetcode-cn.com/problems/wildcard-matching)    
- [10. 正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching)    
  
### $1.3 单串 dp[i][k]，i 是位置，时间，高度等；k 是长度，个数，次数等，k 上可能有二分，贪心等  
- [813. 最大平均值和的分组](https://leetcode-cn.com/problems/largest-sum-of-averages/) k 是个数
- [887. 鸡蛋掉落](https://leetcode-cn.com/problems/super-egg-drop)  k 是次数，k 上有二分    

#### $1.3.1 股票系列: dp[i][k][state] i 是时间，k 是次数，state 是状态机(在某一个位置或者时刻可以选择多种状态)
- [121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock)    
- [122. 买卖股票的最佳时机 II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii)    
- [123. 买卖股票的最佳时机 III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii)    
- [188. 买卖股票的最佳时机 IV](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv)    
- [309. 最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown)    
- [714. 买卖股票的最佳时机含手续费](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee)    
  
### $1.4 矩阵 dp[i][j]  (i, j) 共同表示位置
- [120. 三角形最小路径和](https://leetcode-cn.com/problems/triangle)    
- [64. 最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)  
- [174. 地下城游戏](https://leetcode-cn.com/problems/dungeon-game/)  
- [931. 下降路径最小和](https://leetcode-cn.com/problems/minimum-falling-path-sum/)
#### 两个位置的情况 dp[位置1][位置2]
原始方程是四维, dp[i1][j1][i2][j2], 如果有一个约束条件，可以 dp[i1][i2][k]
- [741. 摘樱桃](https://leetcode-cn.com/problems/cherry-pickup/)  dp[i1][i2][k] k 为步数，另：流量为 2 的最大费用最大流，每个点拆成费用 i 和费用 0 的边
- [1463. 摘樱桃 II](https://leetcode-cn.com/problems/cherry-pickup-ii/) dp[i1][i2][level] level 为层数

  
---
  
[583. 两个字符串的删除操作](https://leetcode-cn.com/problems/delete-operation-for-two-strings/)  
[801. 使序列递增的最小交换次数](https://leetcode-cn.com/problems/minimum-swaps-to-make-sequences-increasing/)  
[97. 交错字符串](https://leetcode-cn.com/problems/interleaving-string/)  
[115. 不同的子序列](https://leetcode-cn.com/problems/distinct-subsequences/)  
[727. 最小窗口子序列](https://leetcode-cn.com/problems/minimum-window-subsequence/)  
  
  
#### 2、区间 DP  
[516. 最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence)    
[730. 统计不同回文子字符串](https://leetcode-cn.com/problems/count-different-palindromic-subsequences)    
[1039. 多边形三角剖分的最低得分](https://leetcode-cn.com/problems/minimum-score-triangulation-of-polygon)    
[664. 奇怪的打印机](https://leetcode-cn.com/problems/strange-printer)    
[312. 戳气球](https://leetcode-cn.com/problems/burst-balloons)    
[1024. 视频拼接]
  
#### 3、背包 DP  
组合问题(求方案数)  
`dp[i] = dp[i] + dp[i - num]`  
[377. 组合总和 Ⅳ](https://leetcode-cn.com/problems/combination-sum-iv/) 顺序不同的序列被视作不同的组合  
[494. 目标和 (01背包-求方案数)](https://leetcode-cn.com/problems/target-sum)    
[518. 零钱兑换 II (完全背包-求方案数)](https://leetcode-cn.com/problems/coin-change-2)    
恰好取到背包容量  
`dp[i] = dp[i] or dp[i - num]`  
[416. 分割等和子集 (01背包-要求恰好取到背包容量)](https://leetcode-cn.com/problems/partition-equal-subset-sum)    
[139]  
最值问题  
`dp[i] = min/max(dp[i], dp[i - num] + 1)`  
[322. 零钱兑换 (完全背包)](https://leetcode-cn.com/problems/coin-change)    
[474. 一和零 (二维费用背包)](https://leetcode-cn.com/problems/ones-and-zeroes)    
  
步骤：  
1. 分析是否为背包问题。  
2. 是以上三种背包问题中的哪一种。  
3. 是0-1背包问题还是完全背包问题。也就是题目给的nums数组中的元素是否可以重复使用。  
4. 如果是组合问题，是否需要考虑元素之间的顺序。需要考虑顺序有顺序的解法，不需要考虑顺序又有对应的解法。  
  
  
#### 4、树形 DP  
[124. 二叉树中的最大路径和](https://leetcode-cn.com/problems/binary-tree-maximum-path-sum)    
[1245. 树的直径 (邻接表上的树形DP)](https://leetcode-cn.com/problems/tree-diameter)    
[543. 二叉树的直径](https://leetcode-cn.com/problems/diameter-of-binary-tree)    
[333. 最大 BST 子树](https://leetcode-cn.com/problems/largest-bst-subtree)    
[337. 打家劫舍 III](https://leetcode-cn.com/problems/house-robber-iii)    
[1372. 二叉树中的最长交错路径](https://leetcode-cn.com/problems/longest-zigzag-path-in-a-binary-tree/)    
  
#### 5、状态压缩 DP  
[464. 我能赢吗](https://leetcode-cn.com/problems/can-i-win)    
[526. 优美的排列](https://leetcode-cn.com/problems/beautiful-arrangement)    
[935. 骑士拨号器](https://leetcode-cn.com/problems/knight-dialer)    
[1349. 参加考试的最大学生数](https://leetcode-cn.com/problems/maximum-students-taking-exam)    
[1371. 每个元音包含偶数次的最长子字符串](https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)    
  
#### 6、数位 DP  
[233. 数字 1 的个数](https://leetcode-cn.com/problems/number-of-digit-one)    
[902. 最大为 N 的数字组合](https://leetcode-cn.com/problems/numbers-at-most-n-given-digit-set)    
[1015. 可被 K 整除的最小整数](https://leetcode-cn.com/problems/smallest-integer-divisible-by-k)    
  
#### 7、计数问题  
计数是组合数学的重要内容。不考虑用母函数等手段求解析解的化，计数问题一般有两种做法
1. 找到组合数公式，然后用 DP 的方式求组合数  
2. 找到递归关系，然后以 DP 的方式求这个递推关系，如果是线性递推关系，可以用矩阵快速幂加速

以卡特兰数为例，
1. 组合数公式: $C_{n} = \dbinom{2n}{n} - \dbinom{2n}{n - 1} = \frac{1}{n + 1}\dbinom{2n}{n} = \prod_{k=2}^{n}\frac{n + k}{k}$
2. 递推式: $C_{n} = \sum_{i=0}^{N-1}C_{i}C_{n-i-1}$  
  
路径问题(组合数学中的格路模型)：  
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

隐晦的递推关系: 
- [935. 骑士拨号器](https://leetcode-cn.com/problems/knight-dialer)    
- [957. N 天后的牢房](https://leetcode-cn.com/problems/prison-cells-after-n-days)    
  
#### 9、概率型 DP  
求概率，求数学期望  
[808. 分汤](https://leetcode-cn.com/problems/soup-servings)    
[837. 新21点](https://leetcode-cn.com/problems/new-21-game)    
  
#### 10、博弈型 DP  
策梅洛定理，SG 定理，minimax  
  
- 翻转游戏  
[293. 翻转游戏](https://leetcode-cn.com/problems/flip-game)    
[294. 翻转游戏 II](https://leetcode-cn.com/problems/flip-game-ii)    
  
- Nim游戏  
[292. Nim 游戏](https://leetcode-cn.com/problems/nim-game)    
石子游戏  
[877. 石子游戏](https://leetcode-cn.com/problems/stone-game)    
[1140. 石子游戏 II](https://leetcode-cn.com/problems/stone-game-ii/)    
  
- 井字游戏  
[348. 判定井字棋胜负](https://leetcode-cn.com/problems/design-tic-tac-toe)    
[794. 有效的井字游戏](https://leetcode-cn.com/problems/valid-tic-tac-toe-state)    
[1275. 找出井字棋的获胜者](https://leetcode-cn.com/problems/find-winner-on-a-tic-tac-toe-game)    
  
#### 11、记忆化搜索  
本质是 dfs + 记忆化，用在状态的转移方向不确定的情况  
[329. 矩阵中的最长递增路径](https://leetcode-cn.com/problems/longest-increasing-path-in-a-matrix) 另：二维的剥洋葱DP，即先通过拓扑排序把顺序找到
[576. 出界的路径数](https://leetcode-cn.com/problems/out-of-boundary-paths)    
  
  
---  
  
#### 1、线性 DP  
  
[115. 不同的子序列](https://leetcode-cn.com/problems/distinct-subsequences/)    
  
[678. 有效的括号字符串](https://leetcode-cn.com/problems/valid-parenthesis-string/) DFS，贪心，双栈，DP  
  
  
#### 5、状态压缩 DP  
[943. 最短超级串](https://leetcode-cn.com/problems/find-the-shortest-superstring/)  最短哈密顿路  
  
#### 6. 数位 DP  
[1397] 字符串上的数位 DP  
  
  
#### 7、计数型 DP  
计数型DP都可以以组合数学的方法写出组合数，然后dp求组合数  
[980. 不同路径 III](https://leetcode-cn.com/problems/unique-paths-iii/)  
  
  
  
#### 11、记忆化搜索  
[139]  
[140]  
- [818. 赛车](https://leetcode-cn.com/problems/race-car/)    
[894]  
[1376]  
[1387]  
[1388]  
[913]  
[131]  
[410]  
  
---  
  
https://github.com/CyC2018/CS-Notes/blob/master/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92.md#4-%E4%BF%A1%E4%BB%B6%E9%94%99%E6%8E%92  
