// Prob2 Longest Substring Without Repeating Characters

/*
 * Given a string, find the length of the longest substring without repeating characters.
 */

 /*
 * Example 1:
 *
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 * Example 2:
 *
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * Example 3:
 *
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 *              Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
 */

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution_2
{
public:
    int lengthOfLongestSubstring(string s) {
        // 边界检查
        if(s.size() == 0)
            return 0;
        // 初始化
        int max_len = 1;
        int current_len = 1;
        int left = 0;
        int right = 0;
        char_of_current_substr.insert(pair<char, int>(s[left], left));
        // 滑动 right, 直至 right == s.size()
        while(++right != (int)s.size())
        {
            // right + 1 后判断s[right]是否在 集合里
            auto iter = char_of_current_substr.find(s[right]);
            if(iter != char_of_current_substr.end())
            {
                // 在集合里,
                // 更新 set(left 到 index 之间的删除，s[right] 保留)
                // 更新好 set 之后，更新 s[right] 对应的值
                // 更新 current_len
                // 再更新left
                int index = char_of_current_substr[s[right]];
                for(int i = left; i < index; ++i)
                {
                    char_of_current_substr.erase(s[i]);
                }
                char_of_current_substr[s[right]] = right;
                current_len -= index - left;
                left = index + 1;
            }
            else
            {
                // 不在集合里，更新max_len, 插入集合
                ++current_len;
                max_len = (max_len > current_len) ? max_len : current_len;
                char_of_current_substr.insert(pair<char, int>(s[right], right));
            }
        }
        return max_len;
    }

    Solution(){}

private:
    unordered_map<char, int> char_of_current_substr;

};

int main()
{
    string s;
    cout << "input string" << endl;
    cin >> s;

    Solution solution;
    int result;
    result = solution.lengthOfLongestSubstring(s);
    cout << result << endl;
}

/* Similar Problem
 * Longest Substring with At Most Two Distinct Characters
 * Longest Substring with At Most K Distinct Characters
 * Subarrays with K Different Integers
 */

#include <bitset>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.empty()) return 0;
        int n = s.size();
        int i = 0, j = 0;
        bitset<128> state;
        int ans = 0;
        while(i < n && j < n)
        {
            // 推进 j
            while(j < n && !state[(int)s[j]])
            {
                state.set((int)s[j]);
                ++j;
            }
            // [i..j-1] 为候选答案
            ans = max(ans, j - i);
            // 推进 i
            if(j == n) break;
            char target = s[j];
            while(s[i] != target)
            {
                state.reset((int)s[i]);
                ++i;
            }
            state.reset((int)s[i]);
            ++i;
        }
        return ans;
    }
};
