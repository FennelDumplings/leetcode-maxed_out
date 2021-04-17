// prob691: Stickers to Spell Word

/*
 * We are given N different types of stickers. Each sticker has a lowercase English word on it.
 * You would like to spell out the given target string by cutting individual letters from your collection of stickers and rearranging them.
 * You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
 * What is the minimum number of stickers that you need to spell out the target? If the task is impossible, return -1.
 */

/*
 * Example 1:
 * Input:
 * ["with", "example", "science"], "thehat"
 * Output:
 * 3
 * Explanation:
 * We can use 2 "with" stickers, and 1 "example" sticker.
 * After cutting and rearrange the letters of those stickers, we can form the target "thehat".
 * Also, this is the minimum number of stickers necessary to form the target string.
 * Example 2:
 * Input:
 * ["notice", "possible"], "basicbasic"
 * Output:
 * -1
 *  Explanation:
 *  We can't form the target "basicbasic" from cutting letters from the given stickers.
 */

/*
 * Note:
 * stickers has length in the range [1, 50].
 * stickers consists of lowercase English words (without apostrophes).
 * target has length in the range [1, 15], and consists of lowercase English letters.
 * In all test cases, all words were chosen randomly from the 1000 most common US English words, and the target was chosen as a concatenation of two random words.
 * The time limit may be more challenging than usual. It is expected that a 50 sticker test case can be solved within 35ms on average.
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <climits>

using namespace std;

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        if(target.empty()) return 0;
        if(stickers.empty()) return -1;
        target_chars = unordered_map<char, PII>();
        items = vector<unordered_map<char, int>>(); // items[i]:= ch -> cnt
        int n = target.size();
        for(int i = 0; i < n; ++i)
        {
            if(target_chars.count(target[i]) == 0)
                target_chars[target[i]] = PII(0, 1);
            else
                ++target_chars[target[i]].second;
        }
        int ii = 0;
        for(auto &ch: target_chars)
        {
            ch.second.first = ii;
            ii += ch.second.second;
            ch.second.second = ii - 1;
        }
        unordered_set<char> tmp;
        for(const string &s: stickers)
        {
            unordered_map<char, int> item;
            for(const char &ch: s)
            {
                if(target_chars.count(ch) > 0)
                {
                    ++item[ch];
                    tmp.insert(ch);
                }
            }
            if(!item.empty())
                items.push_back(item);
        }
        if(tmp.size() < target_chars.size())
            return -1;
        vector<int> dp((1 << n), -1);
        dp[(1 << n) - 1] = 0;
        int ans = solve(0, dp);
        return ans;
    }

private:
    using PII = pair<int, int>;
    unordered_map<char, PII> target_chars; // ch -> [l,r] 数字一的范围 1<<l ~ 1<<r
    vector<unordered_map<char, int>> items; // items[i]:= ch -> cnt

    int solve(int state, vector<int>& dp)
    {
        if(dp[state] != -1) return dp[state];

        int ans = INT_MAX;
        for(const auto &item: items)
        {
            int add_mask = 0;
            for(const auto &info: item)
            {
                // ch: char -> cnt
                char ch = info.first;
                int cnt = info.second;
                int L = target_chars[ch].first;
                int R = target_chars[ch].second;
                // [L, R] 为 state 中，ch 所属的范围，可能已经有前缀 1 了
                int l = L;
                while(l <= R)
                {
                    if((state >> l) & 1)
                        ++l;
                    else
                        break;
                }
                // state >> l 为 0
                if(l > R) continue;
                // [l, r] 为实际 add_mask 的内容
                int r = min(l + cnt - 1, R);
                for(int k = l; k <= r; ++k)
                    add_mask |= (1 << k);
            }
            if(add_mask == 0) continue;
            ans = min(ans, 1 + solve(state | add_mask, dp));
        }
        return dp[state] = ans;
    }
};
