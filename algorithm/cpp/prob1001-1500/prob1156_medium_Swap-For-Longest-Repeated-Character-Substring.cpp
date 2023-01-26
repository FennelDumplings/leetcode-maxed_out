// prob1156: Swap For Longest Repeated Character Substring

/*
 * Given a string text, we are allowed to swap two of the characters in the string. Find the length of the longest substring with repeated characters.
 */

/*
 * Example 1:
 * Input: text = "ababa"
 * Output: 3
 * Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa", which its length is 3.
 * Example 2:
 * Input: text = "aaabaaa"
 * Output: 6
 * Explanation: Swap 'b' with the last 'a' (or the first 'a'), and we get longest repeated character substring "aaaaaa", which its length is 6.
 * Example 3:
 * Input: text = "aaabbaaa"
 * Output: 4
 * Example 4:
 * Input: text = "aaaaa"
 * Output: 5
 * Explanation: No need to swap, longest repeated character substring is "aaaaa", length is 5.
 * Example 5:
 * Input: text = "abcdef"
 * Output: 1
 */

/*
 * Constraints:
 * 1 <= text.length <= 20000
 * text consist of lowercase English characters only.
 */

#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int maxRepOpt1(string text) {
        int n = text.size();
        vector<int> cnt(26, 0);
        for(const char& ch: text) ++cnt[ch - 'a'];
        int result = 0;
        for(char ch = 'a'; ch <= 'z'; ++ch)
        {
            int left = 0;
            while(left < n && text[left] != ch)
                ++left;
            while(left < n)
            {
                int right = left;
                int other = 0;
                while(right < n)
                {
                    if(text[right] != ch)
                    {
                        if(other == 1)
                            break;
                        ++other;
                    }
                    ++right;
                }
                int len = right - left;
                int item = len;
                if(len > cnt[ch - 'a'])
                    --item;
                result = max(result, item);
                while(left < n && text[left] == ch)
                    ++left;
                ++left;
                while(left < n && text[left] != ch)
                    ++left;
            }
        }
        return result;
    }
};
