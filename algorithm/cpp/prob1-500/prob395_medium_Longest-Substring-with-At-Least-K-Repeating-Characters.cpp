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
        int result = 0;
        for(int t = 1; t <= 26; ++t)
        {
            cnt.assign(26, 0);
            int char_num = 0;
            int left = 0, right = 0;
            while(right < n)
            {
                while(right < n && (char_num < t || cnt[s[right] - 'a'] > 0))
                {
                    if(cnt[s[right] - 'a'] == 0)
                        ++char_num;
                    ++cnt[s[right] - 'a'];
                    ++right;
                }
                if(char_num < t) continue;
                if(_check(cnt, k))
                    result = max(result, right - left);
                while(char_num == t)
                {
                    if(cnt[s[left] - 'a'] == 1)
                        --char_num;
                    --cnt[s[left] - 'a'];
                    ++left;
                }
            }
        }
        return result;
    }

private:
    bool _check(const vector<int>& cnt, int t)
    {
        for(int num: cnt)
        {
            if(num != 0 && num < t)
                return false;
        }
        return true;
    }
};

// 分治
// 每次通过字符计数排除一些非法字符，然后得到若干子串
// 然后在子串上继续找非法字符(只适用于该子串)，若某个子串没找到非法字符则计算该子串的贡献的最长值
class Solution_2 {
public:
    int longestSubstring(string s, int k) {
        if(s.empty()) return 0;
        int n = s.size();
        if(k == 0 || k == 1) return n;
        if(n < k) return 0;
        vector<int> cnt(26, 0);
        int result = 0;
        int last_pos = 0; // 用于计算子问题的区间
        bool has_invalad_char = false;
        for(int i = 0; i < n; ++i)
            ++cnt[s[i] - 'a'];
        for(int i = 0; i < n; ++i)
        {
            if(cnt[s[i] - 'a'] < k) // 非法字符
            {
                has_invalad_char = true;
                int l = longestSubstring(s.substr(last_pos, i - last_pos), k);
                result = max(result, l);
                last_pos = i + 1;
            }
        }
        if(!has_invalad_char)
            return s.size();
        // 求解最后一个区间
        result = max(result, longestSubstring(s.substr(last_pos, n - last_pos), k));
        return  result;
    }
};
