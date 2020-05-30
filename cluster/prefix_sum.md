
## $1 裸前缀和
[303. 区域和检索 - 数组不可变](https://leetcode-cn.com/problems/range-sum-query-immutable/)  
[304. 二维区域和检索 - 矩阵不可变](https://leetcode-cn.com/problems/range-sum-query-2d-immutable/)  

## $2 数据结构维护前缀和
- 单调队列维护前缀和在前缀和数组中的索引
[53. 最大子序和](https://leetcode-cn.com/problems/maximum-subarray/)  
[918. 环形子数组的最大和](https://leetcode-cn.com/problems/maximum-sum-circular-subarray/)  


- HashMap 维护，键是前缀和(状态)的值，值为第一次出现时的索引
[325. 和等于 k 的最长子数组长度](https://leetcode-cn.com/problems/maximum-size-subarray-sum-equals-k/)  
[525. 连续数组](https://leetcode-cn.com/problems/contiguous-array/)  
[1371. 每个元音包含偶数次的最长子字符串](https://leetcode-cn.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/): 前缀状态为 a,e,i,o,u 的个数的奇偶  


- HashMap 维护，键是前缀和(前缀状态)的值，值为出现次数
[560. 和为K的子数组](https://leetcode-cn.com/problems/subarray-sum-equals-k/)  
[1248. 统计优美子数组](https://leetcode-cn.com/problems/count-number-of-nice-subarrays/): 前缀状态为奇数的个数  


- HashMap 维护，键是前缀和模 K 的余数(可以理解为前缀状态，状态为前缀和模K)
- - 值为第一次出现时的索引
[523. 连续的子数组和](https://leetcode-cn.com/problems/continuous-subarray-sum/)  
- - 值为出现次数
[974. 和可被 K 整除的子数组](https://leetcode-cn.com/problems/subarray-sums-divisible-by-k/)  


## $3 运算推广
- 前缀积
[152. 乘积最大子数组](https://leetcode-cn.com/problems/maximum-product-subarray/)  
[713. 乘积小于K的子数组](https://leetcode-cn.com/problems/subarray-product-less-than-k/)  


- 前缀异或
[1442. 形成两个异或相等数组的三元组数目](https://leetcode-cn.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/)  
[1310. 子数组异或查询](https://leetcode-cn.com/problems/xor-queries-of-a-subarray/)


- 前缀和(积)与后缀和(积)均需要
[724. 寻找数组的中心索引](https://leetcode-cn.com/problems/find-pivot-index/)  
[238. 除自身以外数组的乘积](https://leetcode-cn.com/problems/product-of-array-except-self/)  


## $4 前缀和维护 dp 数组
[837. 新21点](https://leetcode-cn.com/problems/new-21-game/)  

## $5 其它
[1381. 设计一个支持增量操作的栈](https://leetcode-cn.com/problems/design-a-stack-with-increment-operation/)  



---

## 差分
[370. 区间加法](https://leetcode-cn.com/problems/insert-interval/) 差分  
[1180. 统计只含单一字母的子串](https://leetcode-cn.com/problems/count-substrings-with-only-one-distinct-letter/)  
