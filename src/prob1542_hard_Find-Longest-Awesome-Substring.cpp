// prob1542: Find Longest Awesome Substring

/*
 * https://leetcode-cn.com/problems/find-longest-awesome-substring/
 */

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        int state = 0;
        mapping = unordered_map<int, int>();
        mapping[0] = -1;
        int ans = 1;
        for(int i = 0; i < n; ++i)
        {
            state ^= (1 << (s[i] - '0'));
            if(mapping.count(state) > 0)
            {
                int j = mapping[state];
                ans = max(ans, i - j);
            }
            for(int d = 0; d <= 9; ++d)
            {
                int target = 0;
                target |= (1 << d);
                int gap = get_gap(state, target);
                if(mapping.count(gap) > 0)
                {
                    int j = mapping[gap];
                    ans = max(ans, i - j);
                }
            }
            if(mapping.count(state) == 0)
                mapping[state] = i;
        }
        return ans;
    }

private:
    unordered_map<int, int> mapping;

    int get_gap(int state, int target)
    {
        int ans = 0;
        for(int i = 0; i <= 9; ++i)
            ans |= ((((state >> i) & 1) ^ ((target >> i) & 1)) << i);
        return ans;
    }
};
