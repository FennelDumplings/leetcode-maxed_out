// prob1208: Get Equal Substrings Within Budget

/*
 * https://leetcode-cn.com/problems/get-equal-substrings-within-budget/
 */

#include <string>
#include <cmath>

using namespace std;

class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int n = s.size();
        int left = 0, right = 0;
        int cost = 0;
        int ans = 0;
        while(right < n)
        {
            while(right < n && cost + abs(s[right] - t[right]) <= maxCost)
            {
                cost += abs(s[right] - t[right]);
                ++right;
            }
            ans = max(ans, right - left);
            cost -= abs(s[left] - t[left]);
            ++left;
        }
        return ans;
    }
};
