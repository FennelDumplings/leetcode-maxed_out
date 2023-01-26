// prob1371: Find the Longest Substring Containing Vowels in Even Counts

/*
 * Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
 */

/*
 * Example 1:
 * Input: s = "eleetminicoworoep"
 * Output: 13
 * Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
 * Example 2:
 * Input: s = "leetcodeisgreat"
 * Output: 5
 * Explanation: The longest substring is "leetc" which contains two e's.
 * Example 3:
 * Input: s = "bcbcbc"
 * Output: 6
 * Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.
 */

/*
 * Constraints:
 * 1 <= s.length <= 5 x 10^5
 * s contains only lowercase English letters.
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findTheLongestSubstring(string s) {
        int n = s.size();
        vector<int> prefix_state(1 << 5, -1); // 类似状态压缩的手法，用前 5 位表示 5 个元音字母的状态
        prefix_state[0] = 0;
        int result = 0;
        int cur_state = 0;
        for(int i = 0; i < n; ++i)
        {
            char c = s[i];
            int idx = _id(c);
            if(idx != -1)
                cur_state ^= 1 << idx;
            if(prefix_state[cur_state] == -1)
                prefix_state[cur_state] = i + 1;
            result = max(result, i + 1 - prefix_state[cur_state]);
        }
        return result;
    }

private:
    int _id(const char& ch)
    {
        switch(ch)
        {
            case('a'): return 0;
            case('e'): return 1;
            case('i'): return 2;
            case('o'): return 3;
            case('u'): return 4;
            default: return -1;
        }
    }
};
