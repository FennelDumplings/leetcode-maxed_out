

# 有效括号
有效括号的条件
1. 左括号必须用相同类型的右括号闭合。
2. 左括号必须以正确的顺序闭合。

有效括号的递归定义：
1. 空 ("")
2. "(" + A + ")" 
3. A + B
其中 A 和 B 都是有效的括号字符串，+ 代表字符串的连接。

- [20. 有效的括号](https://leetcode-cn.com/problems/valid-parentheses/) 三种括号，左括号栈
- [678. 有效的括号字符串](https://leetcode-cn.com/problems/valid-parenthesis-string/) DFS，贪心，双栈，DP
- [32. 最长有效括号](https://leetcode-cn.com/problems/longest-valid-parentheses/) 一种括号，左括号栈，计数器代替栈，DP
- [22. 括号生成](https://leetcode-cn.com/problems/generate-parentheses/) DFS

# 使得括号有效
- [301. 删除无效的括号](https://leetcode-cn.com/problems/remove-invalid-parentheses/)  DFS
- [1249. 移除无效的括号](https://leetcode-cn.com/problems/minimum-remove-to-make-valid-parentheses/)  栈+双指针
- [921. 使括号有效的最少添加](https://leetcode-cn.com/problems/minimum-add-to-make-parentheses-valid/) 栈, 贪心

# 含括号的字符串解析
- [856. 括号的分数](https://leetcode-cn.com/problems/score-of-parentheses/)  
- [1087. 字母切换](https://leetcode-cn.com/problems/brace-expansion/)  
- [1096. 花括号展开 II](https://leetcode-cn.com/problems/brace-expansion-ii/)  
- [1021. 删除最外层的括号](https://leetcode-cn.com/problems/remove-outermost-parentheses/)  
- [1190. 反转每对括号间的子串](https://leetcode-cn.com/problems/reverse-substrings-between-each-pair-of-parentheses/)  

---

