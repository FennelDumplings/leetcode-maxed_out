// prob1358: Number of Substrings Containing All Three Characters

/*
 * https://leetcode-cn.com/problems/number-of-substrings-containing-all-three-characters/
 */

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();
        vector<int> state(3, -1);
        int ans = 0;
        for(int i = 0; i < n; ++i)
        {
            state[s[i] - 'a'] = i;
            int t = *min_element(state.begin(), state.end());
            ans += t + 1;
        }
        return ans;
    }
};
