// prob76: Minimum Window Substring

/*
 * Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).
 */

/*
 * Example:
 * Input: S = "ADOBECODEBANC", T = "ABC"
 * Output: "BANC"
 */

/*
 * Note:
 * If there is no such window in S that covers all characters in T, return the empty string "".
 * If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
 */

#include <string>
#include <vector>
#include <climits>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if(s.empty() || t.empty()) return "";
        int n = s.size();
        unordered_map<int, int> hash;
        // 不在 t 中的字符，计数为0
        for(char& c: t)
            ++hash[c];
        int total = hash.size();

        int cnt = 0;
        int res_lr[2] = {0, -1};
        for(int left = 0, right = 0; right < n; ++right)
        {
            // 如果 s[right] 不在 t 中, 直接变成了负数，之后遇到时候会直接跳过
            --hash[s[right]];


            // 若count[s[j]] 被减到0，说明s[j]是T中的，即使在T中出现n次，也全部被window包含了
            if(hash[s[right]] == 0) cnt++;

            while(hash[s[left]] < 0) // 不在 t 中，或者在 t 中但是多余
            {
                ++hash[s[left]];
                ++left;
            }

            // 跟新答案条件 total 个字符均包含了， 且 s 为空或者更长
            // cnt 已经等于 total  后，就不会再减小了，因为只有 hash[s[left]] < 0 时候才会 ++left
            if(cnt == total && (res_lr[1] - res_lr[0] < 0 || res_lr[1] - res_lr[0] + 1 > right - left + 1))
            {
                res_lr[0] = left;
                res_lr[1] = right;
            }
        }
        return s.substr(res_lr[0], res_lr[1] - res_lr[0] + 1);
    }
};
