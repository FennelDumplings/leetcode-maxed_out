// prob159: longest-substring-with-at-most-two-distinct-characters

/*
 * Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.
 */

/*
 * Example 1:
 * Input: "eceba"
 * Output: 3
 * Explanation: t is "ece" which its length is 3.
 * Example 2:
 * Input: "ccaabbb"
 * Output: 5
 * Explanation: t is "aabbb" which its length is 5.
 */

#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        if(n == 1) return 1;

        int left = 0, right = left + 1;
        int count1 = 1, count2 = 0;
        int result = 0;
        while(true)
        {
            char c1 = s[left];
            count1 = count1 > 0 ? count1 : count2;
            while(right < n && s[right] == c1)
            {
                ++right;
                ++count1;
            }
            if(right >= n) return max(result, right - left);
            char c2 = s[right];
            count2 = 0;
            while(right < n && (s[right] == c1 || s[right] == c2))
            {
                if(s[right] == c1) ++count1;
                else ++count2;
                ++right;
            }
            if(right >= n) return max(result, right - left);
            result = max(result, right - left);
            while(count1 > 0 && count2 > 0)
            {
                if(s[left] == c1)
                    --count1;
                else
                    --count2;
                ++left;
            }
        }
    }
};
