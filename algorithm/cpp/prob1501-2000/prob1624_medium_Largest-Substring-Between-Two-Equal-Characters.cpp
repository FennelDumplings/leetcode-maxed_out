// prob1624: Largest Substring Between Two Equal Characters

/*
 * https://leetcode-cn.com/problems/largest-substring-between-two-equal-characters/
 */


#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int maxLengthBetweenEqualCharacters(string s) {
        int n = s.size();
        if(n <= 1) return -1;
        vector<int> mapping(26, -1);
        int ans = -1;
        for(int i = 0; i < n; ++i)
        {
            char ch = s[i];
            int left = mapping[ch - 'a'];
            if(left != -1)
            {
                ans = max(ans, i - left - 1);
            }
            else
                mapping[ch - 'a'] = i;
        }
        return ans;
    }
};
