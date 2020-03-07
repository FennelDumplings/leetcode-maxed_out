// prob395: Longest Substring with At Least K Repeating Characters

/*
 * Find the length of the longest substring T of a given string (consists of lowercase letters only)
 * such that every character in T appears no less than k times.
 */

/*
 * Example 1:
 * Input:
 * s = "aaabb", k = 3
 * Output:
 * 3
 * The longest substring is "aaa", as 'a' is repeated 3 times.
 * Example 2:
 * Input:
 * s = "ababbc", k = 2
 * Output:
 * 5
 * The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
 */

#include <string>
#include <vector>

using namespace std;

// 枚举包含的不同字符数 t
// 对每个 [left, right] 字符数大于 t 的子串，判断 [left, right - 1] 是否合法
class Solution {
public:
    int longestSubstring(string s, int k) {
        if(s.empty()) return 0;
        int n = s.size();
        if(k == 0 || k == 1) return n;
        vector<int> cnt(26, 0);
        for(int t = 1; t <= 26; ++t)
        {
            cnt.clear();
            int char_num = 0;
            int left = 0, right = 0;
            while(right < n && char_num <= t)
            {
                if(cnt[s[right] - 'a'] == 0)
                    ++char_num;
                ++cnt[s[right]];
                ++right;
            }
            if(right == n) continue;
            if(_check(cnt))
                result = max(result, right - left);
        }

    }
};
