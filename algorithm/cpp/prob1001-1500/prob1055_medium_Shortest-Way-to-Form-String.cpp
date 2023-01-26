// prob1055: Shortest Way to Form String

/*
 * From any string, we can form a subsequence of that string by deleting some number of characters (possibly no deletions).
 * Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.
 */

/*
 * Example 1:
 * Input: source = "abc", target = "abcbc"
 * Output: 2
 * Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".
 * Example 2:
 * Input: source = "abc", target = "acdbc"
 * Output: -1
 * Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.
 * Example 3:
 * Input: source = "xyz", target = "xzyxz"
 * Output: 3
 * Explanation: The target string can be constructed as follows "xz" + "y" + "xz".
 */

/*
 * Constraints:
 * Both the source and target strings consist of only lowercase English letters from "a"-"z".
 * The lengths of source and target string are between 1 and 1000.
 */

#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    int shortestWay(string source, string target) {
        string &s = source, &t = target;
        int n = s.size(), m = t.size();
        vector<set<int>> idxs(26); // 字符 -> 若干索引
        for(int i = 0; i < n; ++i)
            idxs[s[i] - 'a'].insert(i);
        for(const char& ch: target)
            if(idxs[ch - 'a'].empty())
                return -1;
        // t 中的字符均在 s 中出现
        vector<int> dp(m, -1); // dp[i] := t[0..i] 所需的 s 个数, dp[0] = 1;
        vector<int> pos(m, -1); // pos[i] := 最优情况下 t[i] 在 s 的位置(下标)
        dp[0] = 1;
        pos[0] = *idxs[t[0] - 'a'].begin();
        for(int i = 1; i < m; ++i)
        {
            // 在 (pos[i - 1]..n-1] 中找 t[i]
            auto it = idxs[t[i] - 'a'].upper_bound(pos[i - 1]);
            if(it == idxs[t[i] - 'a'].end())
            {
                dp[i] = dp[i - 1] + 1;
                pos[i] = *idxs[t[i] - 'a'].begin();
            }
            else
            {
                dp[i] = dp[i - 1];
                pos[i] = *it;
            }
        }
        return dp[m - 1];
    }
};
