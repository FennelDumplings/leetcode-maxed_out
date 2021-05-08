// prob424: Longest Repeating Character Replacement

/*
 * Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.
 * In one operation, you can choose any character of the string and change it to any other uppercase English character.
 * Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.
 */

/*
 * Note:
 * Both the string's length and k will not exceed 10^4.
 */

/*
 * Example 1:
 * Input:
 * s = "ABAB", k = 2
 * Output:
 * 4
 * Explanation:
 * Replace the two 'A's with two 'B's or vice versa.
 * Example 2:
 * Input:
 * s = "AABABBA", k = 1
 * Output:
 * 4
 * Explanation:
 * Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 * The substring "BBBB" has the longest repeating letters, which is 4.
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 字符表来表示窗口，窗口的大小与新字符的最大计数之间的差值表示可以替换的字符个数，
// 当可以替换的字符个数大于k时，我们需要缩小窗口，也就是left右移，直到可以替换的字符个数等于k时，我们可以得到结果。
// 关于maxCount的解释：
// 因为我们只对最长有效的子字符串感兴趣，所以我们的滑动窗口不需要收缩，即使窗口可能覆盖无效的子字符串。
// 我们可以通过在右边添加一个字符来扩展窗口，或者将整个窗口向右边移动一个字符。
// 而且我们只在新字符的计数超过历史最大计数(来自覆盖有效子字符串的前一个窗口)时才增长窗口。
// 也就是说，我们不需要精确的当前窗口的最大计数;我们只关心最大计数是否超过历史最大计数;这只会因为新字符而发生。
class Solution_2 {
public:
    int characterReplacement(string s, int k) {
        int n = s.size();

        int count[26] = {0};//建立字符->字符数量的映射
        int left = 0, right = 0, result = 0, maxCount = 0;

        while(right < n)
        {
            count[s[right] - 'A']++;
            maxCount = max(maxCount, count[s[right] - 'A']);//当前窗口内的最多字符的个数
            if(right - left + 1 - maxCount > k){//需要替换的字符个数就是当前窗口的大小减去窗口中数量最多的字符的数量
                count[s[left] - 'A']--;//缩小窗口
                left++;
            }
            //当窗口内可替换的字符数小于等于k时，我们需要根据该窗口长度来确定是否更新result
            result = max(result, right - left + 1);
            right++;
        }

        return result;
    }
};

#include <algorithm>

class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> cnts(26);
        int n = s.size();
        int left = 0, right = 0;
        int ans = 0;
        while(right < n)
        {
            while(right < n)
            {
                ++cnts[s[right] - 'A'];
                if(!check(cnts, k, left, right))
                    break;
                ++right;
            }
            ans = max(ans, right - left);
            if(right == n) break;
            while(!check(cnts, k, left, right))
            {
                --cnts[s[left] - 'A'];
                ++left;
            }
            ++right;
        }
        return ans;
    }

private:
    bool check(const vector<int>& cnts, int k, int l, int r)
    {
        int max_cnt = 0;
        for(int c: cnts)
        {
            max_cnt = max(max_cnt, c);
        }
        int len = r - l + 1;
        return len - max_cnt <= k;
    }
};
